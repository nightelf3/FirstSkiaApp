#pragma once

#include "BaseValueControl.h"
#include "include/core/SkString.h"

class Slider : public BaseValueControl
{
public:
	Slider(SkScalar value = 0.0f, SkScalar min = 0.0f, SkScalar max = 1.0f, SkString caption = {});

	void Draw(SkCanvas* canvas, const SkRect& bounds) override;
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override;

	SkScalar GetHeight() const override;

private:
	const SkScalar m_Min = 0.0f;
	const SkScalar m_Max = 1.0f;
	const SkString m_Caption;

	bool m_Active = false;
	bool m_MouseDown = false;
};
