#pragma once

#include "BaseControl.h"

class Button : public BaseControl
{
public:
	Button(std::function<void()> action, SkString caption = {});
	~Button() override = default;

	void Draw(SkCanvas* canvas, const SkRect& bounds) override;
	SkScalar GetHeight() const override;

protected:
	void OnMouseUp(int x, int y, ModifierKey modifiers) override;

private:
	std::function<void()> m_Action;
};
