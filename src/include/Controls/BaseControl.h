#pragma once

#include "include/Interfaces/IControl.h"
#include "include/Layers/Utils/Utils.h"

template<typename T>
class BaseControl : public IControl
{
public:
	void Draw(SkCanvas* canvas, const SkRect& bounds)
	{
		m_Bounds = bounds;
	}

	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
	{
		return IsSupportInputState(state) && IsPointInRect(x, y, m_Bounds);
	}

	T GetValue() const { return m_Value; }
	void SetValue(T value) { m_Value = std::move(value); }

protected:
	SkRect GetBounds() const { return m_Bounds; }

	bool IsSupportInputState(InputState state) const
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

private:
	SkRect m_Bounds;
	T m_Value = T{};
};
