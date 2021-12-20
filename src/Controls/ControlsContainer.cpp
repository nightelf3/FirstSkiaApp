#include "include/Controls/ControlsContainer.h"
#include "include/Controls/Focus.h"

#include "include/core/SkCanvas.h"

namespace
{
	constexpr SkScalar kPanelRadius = 10.0f;  // in px
}

ControlsContainer::ControlsContainer(const ContainerParams& params) :
	m_Params(params)
{
}

void ControlsContainer::Draw(SkCanvas* canvas, const SkRect& bounds)
{
	const SkRect panelRect = GetPanelRect(bounds);
	DrawUtils::DrawRoundRect(canvas, panelRect, kPanelRadius, kPanelRadius, m_Params.drawParams);

	const SkRect controlsRect = panelRect.makeInset(m_Params.padding, m_Params.padding);
	SkAutoCanvasRestore guard(canvas, true);
	canvas->clipRect(controlsRect.makeOutset(1.0f, 1.0f));  // fix AA issue

	SkScalar y = controlsRect.top();
	for (auto& control : m_Controls)
	{
		control->Draw(canvas, SkRect::MakeXYWH(controlsRect.left(), y, controlsRect.width(), control->GetHeight()));
		y += control->GetHeight() + m_Params.itemsSpacing;
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
	return height + m_Params.itemsSpacing * (m_Controls.size() - 1) + m_Params.padding * 2.0f;
}

SkRect ControlsContainer::GetPanelRect(SkRect bounds) const
{
	if (m_Params.width >= 0.0f)
		bounds.fLeft = bounds.right() - m_Params.width;
	return SkRect::MakeXYWH(bounds.left(), bounds.top(), bounds.width(),
		std::min(bounds.height(), GetHeight()));
}
