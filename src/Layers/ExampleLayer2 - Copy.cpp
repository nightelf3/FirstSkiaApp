#include "include/Layers/ExampleLayer3.h"
#include "include/core/SkRRect.h"


BaseRandomShape::BaseRandomShape()
{
	m_Paint.setColor(RandomColor());
	m_Paint.setStrokeWidth(RandomScalar(1, 10));
	m_Paint.setStyle(RandomStyle());
}

SkScalar BaseRandomShape::RandomScalar(SkScalar from, SkScalar to) const
{
	return from + static_cast<SkScalar>(rand()) / (static_cast<SkScalar>(RAND_MAX / (to - from)));
}

SkColor BaseRandomShape::RandomColor() const
{
	return SkColorSetARGB(rand() % 0xff, rand() % 0xff, rand() % 0xff, rand() % 0xff);
}

SkPaint::Style BaseRandomShape::RandomStyle() const
{
	return static_cast<SkPaint::Style>(rand() % SkPaint::kStyleCount);
}

RandomRect::RandomRect(int x, int y) :
	BaseRandomShape(),
	m_Rect(SkRect::MakeWH(RandomScalar(100.f, 300.f), RandomScalar(100.f, 300.f)))
{
	m_Rect.offsetTo(x - m_Rect.width(), y - m_Rect.height());
}

void RandomRect::Draw(SkCanvas* canvas)
{
	canvas->drawRect(m_Rect, m_Paint);
}

RandomRRect::RandomRRect(int x, int y) :
	RandomRect(x, y),
	m_Radius(RandomScalar(0.f, 50.f))
{
}

void RandomRRect::Draw(SkCanvas* canvas)
{
	canvas->drawRRect(SkRRect::MakeRectXY(m_Rect, m_Radius, m_Radius), m_Paint);
}

ExampleLayer3::ExampleLayer3()
{
	srand(static_cast<unsigned>(time(0)));
}

void ExampleLayer3::Draw(SkCanvas* canvas)
{
	SkRRect::MakeRectXY()
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	// inititalize paint structure to fill shape with red color
	SkPaint paint;
	paint.setStyle(SkPaint::Style::kFill_Style);
	paint.setColor(SkColors::kRed);

	// get canvas size and resuce it for 1/8
	SkRect rect;
	rect.set(canvas->getDeviceClipBounds());
	rect.inset(rect.width() / 8.f, rect.height() / 8.f);
	canvas->drawOval(rect, paint);
}

bool ExampleLayer3::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override
{

}