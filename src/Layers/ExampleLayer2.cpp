#include "include/Layers/ExampleLayer2.h"
#include "include/Layers/Utils/Utils.h"

void ExampleLayer2::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	// inititalize paint structure to fill shape with red color
	SkPaint paint;
	paint.setStyle(SkPaint::Style::kFill_Style);
	paint.setColor(SkColors::kRed);

	// get canvas size and resuce it for 1/8
	SkRect rect = GetBounds(canvas);
	rect.inset(rect.width() / 8.f, rect.height() / 8.f);
	canvas->drawOval(rect, paint);
}