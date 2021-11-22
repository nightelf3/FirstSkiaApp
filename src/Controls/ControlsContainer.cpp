#include "include/Controls/ControlsContainer.h"
#include "include/Utils/DrawUtils.h"
#include "include/Controls/Focus.h"

#include "include/core/SkCanvas.h"

namespace
{
	constexpr SkScalar kPanelRadius = 10.0f;  // in px
	constexpr SkScalar kPanelPadding = 10.0f;  // in px
	constexpr SkScalar kControlPadding = 4.0f;  // in px

	const DrawUtils::DrawParameters& GetDrawParameters()
	{
		static DrawUtils::DrawParameters params{SkColors::kDkGray.toSkColor() , SkColors::kGray.toSkColor()};
		return params;
	}
}

void ControlsContainer::Draw(SkCanvas* canvas, const SkRect& bounds)
{
	const SkRect panelRect = GetPanelRect(bounds);
	DrawUtils::DrawRoundRect(canvas, panelRect, kPanelRadius, kPanelRadius, GetDrawParameters());

	const SkRect controlsRect = panelRect.makeInset(kPanelPadding, kPanelPadding);
	SkAutoCanvasRestore guard(canvas, true);
	canvas->clipRect(controlsRect.makeOutset(1.0f, 1.0f));  // fix AA issue

	SkScalar y = controlsRect.top();
	for (auto& control : m_Controls)
	{
		control->Draw(canvas, SkRect::MakeXYWH(controlsRect.left(), y, controlsRect.width(), control->GetHeight()));
		y += control->GetHeight() + kControlPadding;
	}
}

bool ControlsContainer::ProcessKey(Key key, InputState state, ModifierKey modifiers)
{
	if (auto control = Focus::GetFocus())
		return control->ProcessKey(key, state, modifiers);
	return false;
}

bool ControlsContainer::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	bool processed = false;
	for (auto& control : m_Controls)
		processed |= control->ProcessMouse(x, y, state, modifiers);
	if (InputState::kDown == state && !processed)
		Focus::SetFocus(nullptr);
	return processed;
}

SkScalar ControlsContainer::GetHeight() const
{
	if (m_Controls.empty())
		return 0.0f;

	SkScalar height = 0.0f;
	for (auto& control : m_Controls)
		height += control->GetHeight();
	return height + kControlPadding * (m_Controls.size() - 1) + kPanelPadding * 2.0f;
}

SkRect ControlsContainer::GetPanelRect(const SkRect& bounds) const
{
	return SkRect::MakeXYWH(bounds.left(), bounds.top(), bounds.width(),
		std::min(bounds.height(), GetHeight()));
}
