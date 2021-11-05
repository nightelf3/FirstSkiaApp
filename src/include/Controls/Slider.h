#pragma once

#include "BaseControl.h"

class Slider : public BaseControl<SkScalar>
{
public:
	void Draw(SkCanvas* canvas, const SkRect& bounds) override;
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override;

private:
	bool m_Active = false;
	bool m_MouseDown = false;
};
