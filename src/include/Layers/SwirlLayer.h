#pragma once

#include "BaseLayer.h"
#include "include/Controls/ControlsContainer.h"
#include "include/effects/SkRuntimeEffect.h"

class SwirlLayer final : public BaseLayer
{
public:
	SwirlLayer();
	std::wstring GetTitle() const override { return L"Swirl"; };
	void Draw(SkCanvas* canvas) override;
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override;

private:
	sk_sp<SkImage> m_Image;
	sk_sp<SkRuntimeEffect> m_Effect;

	ControlsContainer m_Container;
	std::weak_ptr<IControlValue> m_XSlider;
	std::weak_ptr<IControlValue> m_YSlider;
	std::weak_ptr<IControlValue> m_RadiusSlider;
	std::weak_ptr<IControlValue> m_TwistsSlider;
};
