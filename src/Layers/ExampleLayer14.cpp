#include "include/Layers/ExampleLayer14.h"
#include "include/core/SkMaskFilter.h"
#include "include/core/SkFont.h"

void ExampleLayer14::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	SkPaint paint;
	paint.setColor(SkColors::kWhite);
	if (m_bEnableMask)
		paint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, m_Radius));
	const char str[] = "My First Skia App";
	canvas->drawSimpleText(str, strlen(str), SkTextEncoding::kUTF8, 200, 360, {nullptr, 120}, paint);
}

bool ExampleLayer14::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	if (state == InputState::kUp || InputState::kDown == state)
	{
		m_bEnableMask = InputState::kUp == state;
		return true;
	}
	return false;
}

bool ExampleLayer14::ProcessMouseWheel(InputState state, ModifierKey modifiers)
{
	if (InputState::kZoomIn == state)
		m_Radius++;
	else
	{
		m_Radius--;
		if (m_Radius < 0.f)
			m_Radius = 0.f;
	}
	return true;
}