#include "include/Layers/ExampleLayer14.h"
#include "include/Layers/Utils/Utils.h"
#include "include/core/SkMaskFilter.h"
#include "include/core/SkTextBlob.h"

ExampleLayer14::ExampleLayer14()
{
}

void ExampleLayer14::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	SkPaint paint;
	paint.setColor(SkColors::kWhite);
	if (m_bEnableMask)
		paint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, 5.0f));
	sk_sp<SkTextBlob> blob = SkTextBlob::MakeFromString("My First Skia App", SkFont(nullptr, 120));
	canvas->drawTextBlob(blob.get(), 200, 360, paint);
}

bool ExampleLayer14::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	m_bEnableMask = InputState::kUp == state;
	return true;
}