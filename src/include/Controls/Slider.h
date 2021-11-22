#pragma once

#include "BaseControl.h"
#include "BaseValueControl.h"

struct SliderParams : public ValueControlParams
{
	SliderParams(SkScalar value = 0.0f, SkScalar min = 0.0f, SkScalar max = 1.0f, SkScalar increment = 0.1f) :
		ValueControlParams(value, min, max), m_Increment(increment)
	{}

	SkScalar m_Increment = 0.1f;
};

class Slider : public BaseControl, public BaseValueControl<SliderParams>
{
public:
	Slider(const SliderParams& params, SkString caption = {});
	~Slider() override = default;

	void Draw(SkCanvas* canvas, const SkRect& bounds) override;
	SkScalar GetHeight() const override;

private:
	bool OnKey(Key key, InputState state, ModifierKey modifiers) override;
	bool OnMouseDown(int x, int y, ModifierKey modifiers) override;
	void OnMouseMove(int x, int y, ModifierKey modifiers, bool active) override;
	void OnMouseUp(int x, int y, ModifierKey modifiers) override;

	SkRect m_Track;
};
