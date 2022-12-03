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
	bool OnMouseDown(int x, int y, skui::ModifierKey modifiers) override;
	void OnMouseUp(int x, int y, skui::ModifierKey modifiers) override;

private:
	std::function<void()> m_Action;
	bool m_Pressed = false;
};
