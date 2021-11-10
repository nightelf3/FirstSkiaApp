#pragma once

#include "include/Types.h"
#include "include/core/SkSurface.h"

struct IControl
{
	virtual void Draw(SkCanvas* canvas, const SkRect& bounds) = 0;
	virtual bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) = 0;

	virtual SkScalar GetHeight() const = 0;
};

struct IControlValue : public IControl
{
	virtual SkScalar GetValue() const = 0;
	virtual void SetValue(SkScalar value) = 0;
};
