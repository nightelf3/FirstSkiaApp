#pragma once

#include "ILayer.h"

struct IApplication
{
	virtual ~IApplication() = default;
	virtual void Show() = 0;
	virtual void AddLayer(spLayer&& layer) = 0;
	virtual void OnPaint() = 0;
	virtual void OnIdle() = 0;
	virtual void OnResize(int w, int h) = 0;
	virtual bool OnKey(Key key, InputState state, ModifierKey modifiers) = 0;
	virtual bool OnMouse(int x, int y, InputState state, ModifierKey modifiers) = 0;

	virtual void Invalidate() = 0;
	virtual void SwapBuffers() = 0;
};
