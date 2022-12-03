#pragma once

#include "tools/skui/Key.h"
#include "tools/skui/InputState.h"
#include "tools/skui/ModifierKey.h"
#include "include/core/SkSurface.h"

struct IControl
{
	virtual ~IControl() = default;
	virtual void Draw(SkCanvas* canvas, const SkRect& bounds) = 0;
	virtual bool ProcessChar(SkUnichar c, skui::ModifierKey modifiers) = 0;
	virtual bool ProcessKey(skui::Key, skui::InputState state, skui::ModifierKey modifiers) = 0;
	virtual bool ProcessMouse(int x, int y, skui::InputState state, skui::ModifierKey modifiers) = 0;

	virtual SkScalar GetHeight() const = 0;
};
