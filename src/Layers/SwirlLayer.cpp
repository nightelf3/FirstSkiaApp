#include "include/Layers/SwirlLayer.h"
#include "include/Layers/Utils/Utils.h"
#include "include/Controls/Slider.h"

#include "include/core/SkImage.h"

#include <iostream>

namespace
{
	constexpr SkScalar kMinTwists = -6.0f;
	constexpr SkScalar kMaxTwists = 6.0f;
	constexpr SkScalar kPanelSize = 300.0f;  // in px
	constexpr SkScalar kPanelPadding = 10.0f;  // in px

	const std::string SWIRL_SHADER = R"---(
		uniform shader texture;

		uniform float width;
		uniform float height;
		uniform float swirlX;
		uniform float swirlY;
		uniform float swirlRadius;
		uniform float swirlTwists;

		const float PI = 3.14159265359;

		half4 main(float2 p) {
			float2 swirlCenter = float2(swirlX, swirlY);
			float2 pixel = float2(p.x / width, p.y / height) - swirlCenter;
			float pixelLength = length(pixel);

			float swirlAmount = 1.0 - (pixelLength / swirlRadius);
			if (swirlAmount > 0.0)
			{
				float pixelAngle = atan(pixel.y, pixel.x) + swirlTwists * swirlAmount * PI * 2.0;
				pixel.x = cos(pixelAngle) * pixelLength + swirlCenter.x;
				pixel.y = sin(pixelAngle) * pixelLength + swirlCenter.y;
			}
			else
			{
				pixel = float2(p.x / width, p.y / height);
			}

			return texture.eval(float2(pixel.x * width, pixel.y * height));
		})---";

	struct SwirlParameters
	{
		float width = 0.0f;
		float height = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float radius = 0.0f;
		float twist = 0.0f;
	};

	sk_sp<SkShader> CreateBWShader(sk_sp<SkImage> image, sk_sp<SkRuntimeEffect> effect, SwirlParameters& params)
	{
		if (!effect)
			return nullptr;

		sk_sp<SkShader> pColorizerShader = image->makeShader(SkTileMode::kDecal, SkTileMode::kDecal, {}, SkMatrix::I());
		sk_sp<SkData> dataInput = SkData::MakeWithCopy(&params, sizeof(SwirlParameters));
		sk_sp<SkShader> children[] = { pColorizerShader };
		return effect->makeShader(dataInput, children, 1, nullptr, false);
	}

	SkRect GetPanelRect(SkRect bounds)
	{
		bounds.fLeft = bounds.fRight - kPanelSize;
		return bounds.makeInset(kPanelPadding, kPanelPadding);
	}

	SkScalar GetValue(SkScalar value)
	{
		return (kMaxTwists - kMinTwists) * value + kMinTwists;
	}

	SkScalar GetSliderValue(SkScalar value)
	{
		return (value - kMinTwists) / (kMaxTwists - kMinTwists);
	}
}

SwirlLayer::SwirlLayer()
{
	m_Image = LoadImageFromFile(SkString("resources/8k.jpg"));

	m_XSlider = m_Container.AddControl<Slider>(0.5f, SkString{"X:"});
	m_YSlider = m_Container.AddControl<Slider>(0.5f, SkString{"Y:"});
	m_RadiusSlider = m_Container.AddControl<Slider>(0.75f, SkString{"Radius:"});
	m_TwistsSlider = m_Container.AddControl<Slider>(GetSliderValue(0.5f), SkString{"Twists:"});

	const SkRuntimeEffect::Result effect = SkRuntimeEffect::MakeForShader(SkString{SWIRL_SHADER.c_str()});
	if (!effect.effect)
		std::cerr << effect.errorText.c_str();
	m_Effect = effect.effect;
}

void SwirlLayer::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);
	const SkRect bounds = GetBounds(canvas);

	if (m_Effect)
	{
		SkAutoCanvasRestore guard(canvas, true);
		const SkRect imageRect = SkRect::MakeWH(m_Image->width(), m_Image->height());
		canvas->setMatrix(SkMatrix::RectToRect(imageRect, bounds, SkMatrix::kCenter_ScaleToFit));

		SwirlParameters params;
		params.width = imageRect.width();
		params.height = imageRect.height();
		params.x = m_XSlider.lock()->GetValue();
		params.y = m_YSlider.lock()->GetValue();
		params.radius = m_RadiusSlider.lock()->GetValue();
		params.twist = GetValue(m_TwistsSlider.lock()->GetValue());

		SkPaint paint;
		paint.setShader(CreateBWShader(m_Image, m_Effect, params));
		canvas->drawPaint(paint);
	}

	// draw controls
	m_Container.Draw(canvas, GetPanelRect(bounds));
}

bool SwirlLayer::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	return m_Container.ProcessMouse(x, y, state, modifiers);
}