#include "include/Layers/LinearGradient4P_v2.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"

#include "include/Utils/ThemeUtils.h"
#include "include/Controls/Slider.h"
#include "include/Controls/Button.h"

LinearGradient4P_v2::LinearGradient4P_v2() :
	m_Container(ThemeUtils::GetRightContainerParams())
{
	SliderParams params;
	{
		auto&& effectContainer = m_Container.AddControl<ControlsContainer>(ThemeUtils::GetControlsContainerParams());

		params.m_Increment = 0.1f;
		params.m_Min = 0.1f;
		params.m_Max = 2.0f;
		params.m_Value = 1.0f;
		m_ScaleSlider = effectContainer.lock()->AddControl<Slider>(params, SkString{ "Scale:" });

		params.m_Increment = 0.1f;
		params.m_Min = -360.0f;
		params.m_Max = 360.0f;
		params.m_Value = 0.0f;
		m_RotateSlider = effectContainer.lock()->AddControl<Slider>(params, SkString{ "Rotate:" });

		params.m_Increment = 0.1f;
		params.m_Min = -0.9f;
		params.m_Max = 0.9f;
		params.m_Value = 0.0f;
		m_SkewSlider = effectContainer.lock()->AddControl<Slider>(params, SkString{ "Skew:" });

		effectContainer.lock()->AddControl<Button>([this]() {
			m_ScaleSlider.lock()->SetValue(1.0f);
			m_RotateSlider.lock()->SetValue(0.0f);
			m_SkewSlider.lock()->SetValue(0.0f);
		}, SkString{ "Reset" });
	}

	const SkString str{R"---(
		half4 main(float2 p) {
			half3 color_top = mix(half3(1, 0, 0), half3(0, 1, 0), p.x);
			half3 color_bottom = mix(half3(0, 0, 1), half3(1, 1, 0), p.x);
			return mix(color_top, color_bottom, p.y).rgb1;
		}
	)---"};
	auto [effect, error] = SkRuntimeEffect::MakeForShader(str);
	m_Effect = effect;
}

void LinearGradient4P_v2::onPaint(SkSurface* surface)
{
	SkCanvas* canvas = surface->getCanvas();
	const SkRect bounds = SkRect::Make(canvas->getDeviceClipBounds());

	if (m_Effect)
	{
		SkMatrix local = SkMatrix::RectToRect(SkRect::MakeWH(1.0f, 1.0f), bounds);
		local.postScale(m_ScaleSlider.lock()->GetValue(), m_ScaleSlider.lock()->GetValue());
		local.postSkew(m_SkewSlider.lock()->GetValue(), m_SkewSlider.lock()->GetValue());
		local.postRotate(m_RotateSlider.lock()->GetValue(), 0.5f, 0.5f);

		SkPaint paint;
		paint.setShader(m_Effect->makeShader({}, {}, &local));
		canvas->drawPaint(paint);
	}

	// draw controls
	m_Container.Draw(canvas, bounds);
}

bool LinearGradient4P_v2::onKey(skui::Key key, skui::InputState state, skui::ModifierKey modifier)
{
	return m_Container.ProcessKey(key, state, modifier);
}

bool LinearGradient4P_v2::onMouse(int x, int y, skui::InputState state, skui::ModifierKey modifier)
{
	return m_Container.ProcessMouse(x, y, state, modifier);
}