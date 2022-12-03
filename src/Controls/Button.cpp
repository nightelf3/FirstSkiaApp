#include "include/Controls/Button.h"
#include "include/Utils/DrawUtils.h"

#include "include/core/SkCanvas.h"

namespace
{
	constexpr SkScalar kHeight = 20.0f; // in px
}

Button::Button(std::function<void()> action, SkString caption) :
	BaseControl(std::move(caption)),
	m_Action(std::move(action))
{
}

void Button::Draw(SkCanvas* canvas, const SkRect& bounds)
{
	DrawUtils::DrawParameters drawParams = DrawUtils::GetDefaultParameters(IsActive());
	if (m_Pressed)
		drawParams.background = SkColors::kDkGray.toSkColor();
	DrawUtils::DrawRect(canvas, bounds, drawParams);

	{ // draw caption
		SkPaint paint;
		paint.setAntiAlias(true);
		paint.setColor(SkColors::kWhite);
		const SkScalar xOffset = (bounds.width() - DrawUtils::GetTextSize(GetCaption(), paint).width()) / 2.0f;
		DrawUtils::DrawSimpleText(canvas, GetCaption(), DrawUtils::GetTextPoint(GetCaption(), bounds, xOffset, paint), paint);
	}

	return __super::Draw(canvas, bounds);
}

SkScalar Button::GetHeight() const
{
	return kHeight;
}

bool Button::OnMouseDown(int x, int y, skui::ModifierKey modifiers)
{
	m_Pressed = true;
	return true;
}

void Button::OnMouseUp(int x, int y, skui::ModifierKey modifiers)
{
	m_Pressed = false;
	if (m_Action)
		m_Action();
}