#include "include/Controls/Button.h"

#include "include/core/SkCanvas.h"

Button::Button(std::function<void()> action, SkString caption) :
	BaseControl(std::move(caption))
{
}

void Button::Draw(SkCanvas* canvas, const SkRect& bounds)
{
	SkPaint paint;
	paint.setColor(SkColors::kRed);
	canvas->drawRect(bounds, paint);
}

SkScalar Button::GetHeight() const
{
	return 20.0f;
}

void Button::OnMouseUp(int x, int y, ModifierKey modifiers)
{
	if (m_Action)
		m_Action();
}