#include "include/Layers/ExampleLayer3.h"

void ExampleLayer3::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

  SkPaint paint;
  paint.setStyle(SkPaint::kFill_Style);
  paint.setAntiAlias(true);
  paint.setStrokeWidth(4);
  paint.setColor(0xff4285F4);

  SkRect rect = SkRect::MakeXYWH(10, 10, 100, 160);
  canvas->drawRect(rect, paint);

  SkRRect oval;
  oval.setOval(rect);
  oval.offset(40, 80);
  paint.setColor(0xffDB4437);
  canvas->drawRRect(oval, paint);

  paint.setColor(0xff0F9D58);
  canvas->drawCircle(180, 50, 25, paint);

  rect.offset(80, 50);
  paint.setColor(0xffF4B400);
  paint.setStyle(SkPaint::kStroke_Style);
  canvas->drawRoundRect(rect, 10, 10, paint);

	__super::Draw(canvas);
}
