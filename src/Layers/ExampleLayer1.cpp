#include "include/Layers/ExampleLayer1.h"

void ExampleLayer1::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	// inititalize paint structure to fill shape with red color
	SkPaint paint;
	paint.setStyle(SkPaint::Style::kFill_Style);
	paint.setColor(SkColors::kRed);

	// draw 150x100 rect at (100, 100)
	SkRect rect = SkRect::MakeXYWH(100, 100, 150, 100);
	canvas->drawRect(rect, paint);
}