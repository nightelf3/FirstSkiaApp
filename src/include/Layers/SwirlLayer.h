#pragma once

#include "BaseLayer.h"
#include "include/Interfaces/IControlValue.h"
#include "include/Controls/ControlsContainer.h"
#include "include/effects/SkRuntimeEffect.h"

class SwirlLayer final : public BaseLayer
{
public:
	SwirlLayer();
	~SwirlLayer() override = default;

	SkString GetTitle() const override { return SkString{"Swirl"}; };
	void onPaint(SkSurface* surface) override;
	bool onKey(skui::Key key, skui::InputState state, skui::ModifierKey modifier) override;
	bool onMouse(int x, int y, skui::InputState state, skui::ModifierKey modifier) override;

private:
	sk_sp<SkImage> m_Image;
	sk_sp<SkRuntimeEffect> m_Effect;

	ControlsContainer m_Container;
	std::weak_ptr<IControlValue> m_XSlider;
	std::weak_ptr<IControlValue> m_YSlider;
	std::weak_ptr<IControlValue> m_RadiusSlider;
	std::weak_ptr<IControlValue> m_TwistsSlider;
};
