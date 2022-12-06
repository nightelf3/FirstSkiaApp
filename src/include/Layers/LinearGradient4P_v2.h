#pragma once

#include "BaseLayer.h"
#include "include/Interfaces/IControlValue.h"
#include "include/Controls/ControlsContainer.h"
#include "include/effects/SkRuntimeEffect.h"

class LinearGradient4P_v2 final : public BaseLayer
{
public:
	LinearGradient4P_v2();
	~LinearGradient4P_v2() override = default;

	SkString GetTitle() const override { return SkString{"4P Linear Gradient V2"}; };
	void onPaint(SkSurface* surface) override;
	bool onKey(skui::Key key, skui::InputState state, skui::ModifierKey modifier) override;
	bool onMouse(int x, int y, skui::InputState state, skui::ModifierKey modifier) override;

private:
	sk_sp<SkRuntimeEffect> m_Effect;

	ControlsContainer m_Container;
	std::weak_ptr<IControlValue> m_ScaleSlider;
	std::weak_ptr<IControlValue> m_RotateSlider;
	std::weak_ptr<IControlValue> m_SkewSlider;
};
