#ifndef ILAYER_H_35EA475D_38E7_4303_A46E_270BBB4F1377
#define ILAYER_H_35EA475D_38E7_4303_A46E_270BBB4F1377

#include "Types.h"
#include "include/core/SkSurface.h"

struct ILayer
{
	virtual void Draw(SkSurface* surface) = 0;
	virtual void Resize(int w, int h) = 0;
	virtual bool ProcessKey(Key key, InputState state, ModifierKey modifiers) = 0;
	virtual bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) = 0;
	virtual bool ProcessMouseWheel(InputState state, ModifierKey modifiers) = 0;
	virtual bool DrawOnIdle() const = 0;
};

#endif // ILAYER_H_35EA475D_38E7_4303_A46E_270BBB4F1377
