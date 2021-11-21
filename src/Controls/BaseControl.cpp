#include "include/Controls/BaseControl.h"
#include "include/Utils/Utils.h"

BaseControl::~BaseControl() = default;
BaseControl::BaseControl(SkString caption) :
	m_Caption(std::move(caption))
{
}

bool BaseControl::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	m_Active = m_MouseDown || IsSupportInputState(state) && IsPointInRect(x, y, m_Bounds);
	if (!m_Active)
		return false;

	switch (state)
	{
	case InputState::kDown:
		m_MouseDown = true;
		OnMouseDown(x, y, modifiers);
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