#include "include/Layers/ExampleLayer1.h"

void ExampleLayer1::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	// inititalize paint structure to fill shape with red color
	SkPaint paint;
	paint.setStyle(SkPaint::Style::kFill_Style);
	paint.setColor(SkColors::kRed);

	// get canvas size and resuce size for 1/4
	SkRect rect;
	rect.set(canvas->getDeviceClipBounds());
	rect.inset(rect.width() / 8.f, rect.height() / 8.f);
	canvas->drawOval(rect, paint);
}