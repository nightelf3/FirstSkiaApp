#include "include/Layers/ExampleLayer8.h"

void ExampleLayer8::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

  SkAutoCanvasRestore checkpoint(canvas, true);

	canvas->translate(m_Point.x(), m_Point.y());
  canvas->rotate(60.f);
  SkRect rect = SkRect::MakeXYWH(330, -330, 400, 300);

  SkPaint paint;
  paint.setAntiAlias(true);
  paint.setColor(0xff4285F4);
  canvas->drawRect(rect, paint);

  canvas->rotate(20.f);
	canvas->scale(1.2f, 1.2f);
  paint.setColor(0xffDB4437);
  canvas->drawRect(rect, paint);
}

bool ExampleLayer8::ProcessKey(Key key, InputState state, ModifierKey modifiers)
{
	constexpr SkScalar increment = 10.f;
	switch (key)
	{
	case Key::kUp:
		m_Point.fY -= increment;
		return true;

	case Key::kRight:
		m_Point.fX += increment;
		return true;

	case Key::kDown:
		m_Point.fY += increment;
		return true;

	case Key::kLeft:
		m_Point.fX -= increment;
		return true;
	}
	return false;
}