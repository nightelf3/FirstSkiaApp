#include "include/Controls/BaseControl.h"
#include "include/Utils/Utils.h"
#include "include/Controls/Focus.h"

BaseControl::~BaseControl() = default;
BaseControl::BaseControl(SkString caption) :
	m_Caption(std::move(caption))
{
}

bool BaseControl::ProcessKey(Key key, InputState state, ModifierKey modifiers)
{
	return OnKey(key, state, modifiers);
}

bool BaseControl::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	const bool isProcessEvent = m_MouseDown || IsSupportInputState(state) && Utils::IsPointInRect(x, y, m_Bounds);
	m_Active = isProcessEvent || Focus::IsInFocus(this);
	if (!isProcessEvent)
		return false;

	switch (state)
	{
	case InputState::kDown:
		m_MouseDown = OnMouseDown(x, y, modifiers);
		Focus::SetFocus(this);
		break;

	case InputState::kMove:
		OnMouseMove(x, y, modifiers, m_MouseDown);
		break;

	case InputState::kUp:
		if (m_MouseDown)
			OnMouseUp(x, y, modifiers);
		m_MouseDown = false;
		break;
	}

	return true;
}

bool BaseControl::IsSupportInputState(InputState state) const
{
	switch (state)
	{
	case InputState::kDown:
	case InputState::kUp:
	case InputState::kMove:
		return true;
	}
	return false;
}