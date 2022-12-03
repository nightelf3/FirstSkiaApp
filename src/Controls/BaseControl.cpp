#include "include/Controls/BaseControl.h"
#include "include/Utils/Utils.h"
#include "include/Controls/Focus.h"

BaseControl::~BaseControl() = default;
BaseControl::BaseControl(SkString caption) :
	m_Caption(std::move(caption))
{
}

bool BaseControl::ProcessChar(SkUnichar c, skui::ModifierKey modifiers)
{
	return OnChar(c, modifiers);
}

bool BaseControl::ProcessKey(skui::Key key, skui::InputState state, skui::ModifierKey modifiers)
{
	return OnKey(key, state, modifiers);
}

bool BaseControl::ProcessMouse(int x, int y, skui::InputState state, skui::ModifierKey modifiers)
{
	const bool isProcessEvent = m_MouseDown || IsSupportInputState(state) && Utils::IsPointInRect(x, y, m_Bounds);
	m_Active = isProcessEvent || Focus::IsInFocus(this);
	if (!isProcessEvent)
		return false;

	switch (state)
	{
	case skui::InputState::kDown:
		m_MouseDown = OnMouseDown(x, y, modifiers);
		Focus::SetFocus(this);
		break;

	case skui::InputState::kMove:
		OnMouseMove(x, y, modifiers, m_MouseDown);
		break;

	case skui::InputState::kUp:
		if (m_MouseDown)
			OnMouseUp(x, y, modifiers);
		m_MouseDown = false;
		break;
	}

	return true;
}

bool BaseControl::IsSupportInputState(skui::InputState state) const
{
	switch (state)
	{
	case skui::InputState::kDown:
	case skui::InputState::kUp:
	case skui::InputState::kMove:
		return true;
	}
	return false;
}