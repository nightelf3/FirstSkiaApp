#pragma once

#include "BaseLayer.h"
#include "include/Interfaces/IControlValue.h"
#include "include/Controls/ControlsContainer.h"
#include "include/effects/SkRuntimeEffect.h"

enum class FillType
{
	Linear,
	Circular,
	Conical,
	Rectangular
};

class FillLayer final : public BaseLayer
{
public:
	FillLayer();
	~FillLayer() override = default;

	std::wstring GetTitle() const override;
	void Draw(SkCanvas* canvas) override;
	bool ProcessKey(Key key, InputState state, ModifierKey modifiers) override;
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override;

private:
	SkScalar m_Zoom = 1.0f;
	SkPoint m_Pan = SkPoint::Make(0.0f, 0.0f);
	FillType m_FillType = FillType::Linear;

	bool m_MouseDown = false;
	SkPoint m_ptMouse;

	ControlsContainer m_Container;
	std::weak_ptr<IControlValue> m_StepsSlider;
	std::weak_ptr<IControlValue> m_ScaleSlider;
	std::weak_ptr<IControlValue> m_RotateSlider;
	std::weak_ptr<IControlValue> m_SkewSlider;
};
