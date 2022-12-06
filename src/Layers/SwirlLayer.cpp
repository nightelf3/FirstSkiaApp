#include "include/Layers/SwirlLayer.h"
#include "include/Utils/Shaders.h"
#include "include/Utils/Utils.h"
#include "include/Utils/ThemeUtils.h"
#include "include/Controls/Slider.h"
#include "include/Controls/Button.h"

namespace
{
	struct SwirlParameters
	{
		SkScalar x = 0.5f;
		SkScalar y = 0.5f;
		SkScalar radius = 0.75f;
		SkScalar twist = 0.0f;
	};
	constexpr SwirlParameters kSwirlDefault;

	enum class Controls
	{
		kX,
		kY,
		kRadius,
		kTwist
	};

	SliderParams CreateSliderParams(Controls control)
	{
		SliderParams params;
		switch (control)
		{
		case Controls::kX:
			params.m_Value = kSwirlDefault.x;
			break;
		case Controls::kY:
			params.m_Value = kSwirlDefault.y;
			break;
		case Controls::kRadius:
			params.m_Value = kSwirlDefault.radius;
			break;
		case Controls::kTwist:
			params.m_Min = -2.0;
			params.m_Max = 2.0;
			params.m_Value = kSwirlDefault.twist;
			break;
		}
		return params;
	}
}

SwirlLayer::SwirlLayer() : m_Container(ThemeUtils::GetRightContainerParams())
{
	m_Image = Utils::LoadImageFromFile(SkString{"resources/4k.jpg"});

	auto&& effectContainer = m_Container.AddControl<ControlsContainer>(ThemeUtils::GetControlsContainerParams());
	m_XSlider = effectContainer.lock()->AddControl<Slider>(CreateSliderParams(Controls::kX), SkString{"X:"});
	m_YSlider = effectContainer.lock()->AddControl<Slider>(CreateSliderParams(Controls::kY), SkString{"Y:"});
	m_RadiusSlider = effectContainer.lock()->AddControl<Slider>(CreateSliderParams(Controls::kRadius), SkString{"Radius:"});
	m_TwistsSlider = effectContainer.lock()->AddControl<Slider>(CreateSliderParams(Controls::kTwist), SkString{"Twists:"});
	effectContainer.lock()->AddControl<Button>([this]() {
		m_XSlider.lock()->SetValue(kSwirlDefault.x);
		m_YSlider.lock()->SetValue(kSwirlDefault.y);
		m_RadiusSlider.lock()->SetValue(kSwirlDefault.radius);
		m_TwistsSlider.lock()->SetValue(kSwirlDefault.twist);
	}, SkString{"Reset"});


	const SkString str{ R"---(
		uniform shader texture;

		uniform float2 swirlCenter;
		uniform float swirlRadius;
		uniform float swirlTwists;

		const float PI = 3.14159265359;

		half4 main(float2 p) {
			float2 pixel = p - swirlCenter;
			float pixelLength = length(pixel);

			float swirlAmount = 1.0 - (pixelLength / (swirlRadius + 1e-10));
			float pixelAngle = atan(pixel.y, pixel.x) + swirlTwists * swirlAmount * PI * 2.0;
			pixel.x = mix(cos(pixelAngle) * pixelLength + swirlCenter.x, p.x, step(swirlAmount, 0.0));
			pixel.y = mix(sin(pixelAngle) * pixelLength + swirlCenter.y, p.y, step(swirlAmount, 0.0));

			return texture.eval(pixel);
		}
	)---" };
	m_Effect = std::move(SkRuntimeEffect::MakeForShader(str).effect);
}

void SwirlLayer::onPaint(SkSurface* surface)
{
	SkCanvas* canvas = surface->getCanvas();

	// clear canvas with black color
	canvas->clear(SkColors::kBlack);
	const SkRect bounds = Utils::GetBounds(canvas);

	if (m_Effect)
	{
		SkAutoCanvasRestore guard(canvas, true);
		const SkRect imageRect = SkRect::MakeWH(m_Image->width(), m_Image->height());
		canvas->setMatrix(SkMatrix::RectToRect(imageRect, bounds, SkMatrix::kCenter_ScaleToFit));

		SwirlParameters params;
		params.x = m_XSlider.lock()->GetValue();
		params.y = m_YSlider.lock()->GetValue();
		params.radius = m_RadiusSlider.lock()->GetValue();
		params.twist = m_TwistsSlider.lock()->GetValue();

		/**
		*  SkTileMode
		*
		*  SkTileMode::kClamp: replicate the edge color if the shader draws outside of
		*  its original bounds.
		*
		*  SkTileMode::kRepeat: repeat the shader's image horizontally and vertically.
		*
		*  SkTileMode::kMirror: repeat the shader's image horizontally and vertically,
		*  alternating mirror images so that adjacent images always seam.
		*
		*  SkTileMode::kDecal: Only draw within the original domain, return transparent-black
		*  everywhere else.
		*
		*
		*  SkSamplingOptions
		* 
		*  SkFilterMode::kNone: do not perform any sampling
		*
		*  SkFilterMode::kLinear: perform linear interpolation between points
		* 
		*	 SkCubicResampler::Mitchell(): use cubic sampling with Mitchel coeficients
		*
		*	 SkCubicResampler::CatmullRom(): use cubic sampling with CatmullRom coeficients
		*/
		const SkMatrix localImage = SkMatrix::RectToRect(imageRect, SkRect::MakeWH(1.0f, 1.0f), SkMatrix::kFill_ScaleToFit);
		sk_sp<SkShader> pColorizerShader = m_Image->makeShader(SkTileMode::kDecal, SkTileMode::kDecal, SkSamplingOptions{SkFilterMode::kLinear}, &localImage);

		sk_sp<SkData> dataInput = SkData::MakeWithCopy(&params, sizeof(SwirlParameters));
		sk_sp<SkShader> children[] = { pColorizerShader };
		const SkMatrix local = SkMatrix::RectToRect(SkRect::MakeWH(1.0f, 1.0f), imageRect, SkMatrix::kFill_ScaleToFit);

		SkPaint paint;
		paint.setShader(m_Effect->makeShader(dataInput, children, 1, &local));
		canvas->drawPaint(paint);
	}

	// draw controls
	m_Container.Draw(canvas, bounds);
}

bool SwirlLayer::onKey(skui::Key key, skui::InputState state, skui::ModifierKey modifier)
{
	return m_Container.ProcessKey(key, state, modifier);
}

bool SwirlLayer::onMouse(int x, int y, skui::InputState state, skui::ModifierKey modifier)
{
	return m_Container.ProcessMouse(x, y, state, modifier);
}
