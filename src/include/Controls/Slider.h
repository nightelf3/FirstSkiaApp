#pragma once

#include "BaseValueControl.h"
#include "include/core/SkString.h"

class Slider : public BaseValueControl
{
public:
	Slider(SkString caption = {});

	void Draw(SkCanvas* canvas, const SkRect& bounds) override;
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override;

	SkScalar GetHeight() const override;

private:
	SkString m_Caption;
	bool m_Active = false;
	bool m_MouseDown = false;
};
