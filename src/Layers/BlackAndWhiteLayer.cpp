#include "include/Layers/BlackAndWhiteLayer.h"
#include "include/Utils/Shaders.h"
#include "include/Utils/Utils.h"
#include "include/Utils/ThemeUtils.h"
#include "include/Controls/Slider.h"
#include "include/Controls/Button.h"

#include "include/core/SkImage.h"

namespace
{
	enum class Controls
	{
		kRed,
		kYellow,
		kGreen,
		kCyan,
		kBlue,
		kMagenta
	};

	SliderParams CreateSliderParams(Controls control)
	{
		constexpr SkScalar kMin = -2.0f;
		constexpr SkScalar kMax = 3.0f;
		static const SliderParams kDefaultParams(0.0f, kMin, kMax, 0.1f);

		SliderParams params = kDefaultParams;
		switch (control)
		{
		case Controls::kRed:
			params.m_Value = Shaders::kBWDefault.red;
			break;
		case Controls::kYellow:
			params.m_Value = Shaders::kBWDefault.yellow;
			break;
		case Controls::kGreen:
			params.m_Value = Shaders::kBWDefault.green;
			break;
		case Controls::kCyan:
			params.m_Value = Shaders::kBWDefault.cyan;
			break;
		case Controls::kBlue:
			params.m_Value = Shaders::kBWDefault.blue;
			break;
		case Controls::kMagenta:
			params.m_Value = Shaders::kBWDefault.magenta;
			break;
		}
		return params;
	}
}

BlackAndWhiteLayer::BlackAndWhiteLayer() :
	m_Container(ThemeUtils::GetRightContainerParams())
{
	m_Image = Utils::LoadImageFromFile(SkString{"resources/4k.jpg"});

	auto&& effectContainer = m_Container.AddControl<ControlsContainer>(ThemeUtils::GetControlsContainerParams());
	m_RedSlider = effectContainer.lock()->AddControl<Slider>(CreateSliderParams(Controls::kRed), SkString{"Red:"});
	m_YellowSlider = effectContainer.lock()->AddControl<Slider>(CreateSliderParams(Controls::kYellow), SkString{"Yellow:"});
	m_GreenSlider = effectContainer.lock()->AddControl<Slider>(CreateSliderParams(Controls::kGreen), SkString{"Green:"});
	m_CyanSlider = effectContainer.lock()->AddControl<Slider>(CreateSliderParams(Controls::kCyan), SkString{"Cyan:"});
	m_BlueSlider = effectContainer.lock()->AddControl<Slider>(CreateSliderParams(Controls::kBlue), SkString{"Blue:"});
	m_MagentaSlider = effectContainer.lock()->AddControl<Slider>(CreateSliderParams(Controls::kMagenta), SkString{"Magenta:"});
	effectContainer.lock()->AddControl<Button>([this]() {
		m_RedSlider.lock()->SetValue(Shaders::kBWDefault.red);
		m_YellowSlider.lock()->SetValue(Shaders::kBWDefault.yellow);
		m_GreenSlider.lock()->SetValue(Shaders::kBWDefault.green);
		m_CyanSlider.lock()->SetValue(Shaders::kBWDefault.cyan);
		m_BlueSlider.lock()->SetValue(Shaders::kBWDefault.blue);
		m_MagentaSlider.lock()->SetValue(Shaders::kBWDefault.magenta);
	}, SkString{"Reset"});

	auto [effect, error] = Shaders::LoadFromFile(SkString{"resources/shaders/BlackAndWhite.sksl"});
	m_Effect = effect;
}

void BlackAndWhiteLayer::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);
	const SkRect bounds = Utils::GetBounds(canvas);

	if (m_Effect)
	{
		SkAutoCanvasRestore guard(canvas, true);
		const SkRect imageRect = SkRect::MakeWH(m_Image->width(), m_Image->height());
		canvas->setMatrix(SkMatrix::RectToRect(imageRect, bounds, SkMatrix::kCenter_ScaleToFit));

		Shaders::BWParameters params;
		params.red = m_RedSlider.lock()->GetValue();
		params.yellow = m_YellowSlider.lock()->GetValue();
		params.green = m_GreenSlider.lock()->GetValue();
		params.cyan = m_CyanSlider.lock()->GetValue();
		params.blue = m_BlueSlider.lock()->GetValue();
		params.magenta = m_MagentaSlider.lock()->GetValue();

		SkPaint paint;
		paint.setShader(Shaders::CreateShader(m_Image, m_Effect, params));
		canvas->drawPaint(paint);
	}

	// draw controls
	m_Container.Draw(canvas, bounds);
}

bool BlackAndWhiteLayer::ProcessKey(Key key, InputState state, ModifierKey modifiers)
{
	return m_Container.ProcessKey(key, state, modifiers);
}

bool BlackAndWhiteLayer::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	return m_Container.ProcessMouse(x, y, state, modifiers);
}