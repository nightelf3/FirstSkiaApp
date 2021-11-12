#pragma once

#include "BaseControl.h"
#include "BaseValueControl.h"

class Slider : public BaseControl, public BaseValueControl
{
public:
	Slider(SkScalar value = 0.0f, SkScalar min = 0.0f, SkScalar max = 1.0f, SkString caption = {});
	~Slider() override = default;

	void Draw(SkCanvas* canvas, const SkRect& bounds) override;
	SkScalar GetHeight() const override;

protected:
	void OnMouseDown(int x, int y, ModifierKey modifiers) override;
	void OnMouseMove(int x, int y, ModifierKey modifiers, bool active) override;
	void OnMouseUp(int x, int y, ModifierKey modifiers) override;
};
