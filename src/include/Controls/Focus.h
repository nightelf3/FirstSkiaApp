#pragma once

#include "include/Interfaces/IControl.h"

namespace Focus
{
	IControl* GetFocus();
	bool IsInFocus(IControl* control);
	void SetFocus(IControl* control);
};