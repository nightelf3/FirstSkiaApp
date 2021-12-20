#include "include/Layers/SwirlLayer.h"
#include "include/Utils/Shaders.h"
#include "include/Utils/Utils.h"
#include "include/Utils/ThemeUtils.h"
#include "include/Controls/Slider.h"
#include "include/Controls/Button.h"

namespace
{
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
			params.m_Value = Shaders::kSwirlDefault.x;
			break;
		case Controls::kY:
			params.m_Value = Shaders::kSwirlDefault.y;
			break;
		case Controls::kRadius:
			params.m_Value = Shaders::kSwirlDefault.radius;
			break;
		case Controls::kTwist:
			params.m_Min = -2.0;
			params.m_Max = 2.0;
			params.m_Value = Shaders::kSwirlDefault.twist;
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
		m_XSlider.lock()->SetValue(Shaders::kSwirlDefault.x);
		m_YSlider.lock()->SetValue(Shaders::kSwirlDefault.y);
		m_RadiusSlider.lock()->SetValue(Shaders::kSwirlDefault.radius);
		m_TwistsSlider.lock()->SetValue(Shaders::kSwirlDefault.twist);
	}, SkString{"Reset"});

	auto [effect, error] = Shaders::LoadFromFile(SkString{"resources/shaders/Swirl.sksl"});
	m_Effect = effect;
}

void SwirlLayer::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);
	const SkRect bounds = Utils::GetBounds(canvas);

	if (m_Effect)
	{
		SkAutoCanvasRestore guard(canvas, true);
		const SkRect imageRect = SkRect::MakeWH(m_Image->width(), m_Image->height());
		canvas->setMatrix(SkMatrix::RectToRect(imageRect, bounds, SkMatrix::kCenter_ScaleToFit));

		Shaders::SwirlParameters params;
		params.width = imageRect.width();
		params.height = imageRect.height();
		params.x = m_XSlider.lock()->GetValue();
		params.y = m_YSlider.lock()->GetValue();
		params.radius = m_RadiusSlider.lock()->GetValue();
		params.twist = m_TwistsSlider.lock()->GetValue();

		SkPaint paint;
		paint.setShader(Shaders::CreateShader(m_Image, m_Effect, params));
		canvas->drawPaint(paint);
	}

	// draw controls
	m_Container.Draw(canvas, bounds);
}

bool SwirlLayer::ProcessKey(Key key, InputState state, ModifierKey modifiers)
{
	return m_Container.ProcessKey(key, state, modifiers);
}

bool SwirlLayer::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	return m_Container.ProcessMouse(x, y, state, modifiers);
}