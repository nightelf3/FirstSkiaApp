#pragma once

#include "include/Types.h"
#include "include/core/SkSurface.h"

struct IControl
{
	virtual ~IControl() = default;
	virtual void Draw(SkCanvas* canvas, const SkRect& bounds) = 0;
	virtual bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) = 0;

	virtual SkScalar GetHeight() const = 0;
};
