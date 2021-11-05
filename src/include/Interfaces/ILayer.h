#pragma once

#include "include/Types.h"
#include "include/core/SkCanvas.h"

struct ILayer
{
	virtual ~ILayer() = default;
	virtual void Draw(SkCanvas* canvas) = 0;
	virtual std::wstring GetTitle() const = 0;
	virtual bool ProcessKey(Key key, InputState state, ModifierKey modifiers) = 0;
	virtual bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) = 0;
	virtual bool ProcessMouseWheel(InputState state, ModifierKey modifiers) = 0;
};

using spLayer = std::shared_ptr<ILayer>;
