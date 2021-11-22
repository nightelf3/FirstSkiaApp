#include "include/Controls/Focus.h"

namespace
{
	static IControl* gFocusControl = nullptr;
}

IControl* Focus::GetFocus()
{
	return gFocusControl;
}

bool Focus::IsInFocus(IControl* control)
{
	return gFocusControl == control;
}

void Focus::SetFocus(IControl* control)
{
	gFocusControl = control;
}