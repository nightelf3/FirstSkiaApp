#ifndef ILAYER_H_35EA475D_38E7_4303_A46E_270BBB4F1377
#define ILAYER_H_35EA475D_38E7_4303_A46E_270BBB4F1377

#include "include/Types.h"
#include "include/core/SkCanvas.h"

struct ILayer
{
	virtual void Draw(SkCanvas* canvas) = 0;
	virtual void Resize(int w, int h) = 0;
	virtual bool ProcessKey(Key key, InputState state, ModifierKey modifiers) = 0;
	virtual bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) = 0;
	virtual bool ProcessMouseWheel(InputState state, ModifierKey modifiers) = 0;
	virtual bool DrawOnIdle() const = 0;
};

using spLayer = std::shared_ptr<ILayer>;

#endif // ILAYER_H_35EA475D_38E7_4303_A46E_270BBB4F1377
