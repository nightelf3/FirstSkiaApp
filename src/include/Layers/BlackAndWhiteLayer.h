#pragma once

#include "BaseLayer.h"
#include "include/Interfaces/IControlValue.h"
#include "include/Controls/ControlsContainer.h"
#include "include/effects/SkRuntimeEffect.h"

class BlackAndWhiteLayer final : public BaseLayer
{
public:
	BlackAndWhiteLayer();
	~BlackAndWhiteLayer() override = default;

	std::wstring GetTitle() const override { return L"Black & White"; };
	void Draw(SkCanvas* canvas) override;
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override;

private:
	sk_sp<SkImage> m_Image;
	sk_sp<SkRuntimeEffect> m_Effect;

	ControlsContainer m_Container;
	std::weak_ptr<IControlValue> m_RedSlider;
	std::weak_ptr<IControlValue> m_YellowSlider;
	std::weak_ptr<IControlValue> m_GreenSlider;
	std::weak_ptr<IControlValue> m_CyanSlider;
	std::weak_ptr<IControlValue> m_BlueSlider;
	std::weak_ptr<IControlValue> m_MagentaSlider;
};
