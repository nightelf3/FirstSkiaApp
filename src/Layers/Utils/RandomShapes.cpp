#include "include/Layers/Utils/RandomShapes.h"
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
	m_Rect.offsetTo(x - m_Rect.width() / 2.f, y - m_Rect.height() / 2.f);
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

RandomCircle::RandomCircle(int x, int y) :
	BaseRandomShape(),
	m_Center(SkPoint::Make(x, y)),
	m_Radius(RandomScalar(10.f, 200.f))
{
}

void RandomCircle::Draw(SkCanvas* canvas)
{
	canvas->drawCircle(m_Center, m_Radius, m_Paint);
}

RandomPath::RandomPath(int x, int y) :
	BaseRandomShape()
{
	m_Path.moveTo(x, y);
	SkRect rect = SkRect::MakeWH(RandomScalar(100.f, 300.f), RandomScalar(100.f, 300.f));
	rect.offsetTo(x - rect.width() / 2.f, y - rect.height() / 2.f);
	m_Path.addArc(rect, RandomScalar(0.f, 360.f), RandomScalar(0.f, 360.f));
}

void RandomPath::Draw(SkCanvas* canvas)
{
	canvas->drawPath(m_Path, m_Paint);
}

BaseRandomShapeLayer::BaseRandomShapeLayer()
{
	srand(static_cast<unsigned>(time(0)));
}

void BaseRandomShapeLayer::Draw(SkCanvas* canvas)
{
	// draw all shapes
	for (auto& shape : m_Shapes)
		shape->Draw(canvas);
}

bool BaseRandomShapeLayer::ProcessKey(Key key, InputState state, ModifierKey modifiers)
{
	if (state != InputState::kDown)
		return false;

	if (key == Key::kDelete)
	{
		m_Shapes.clear();
		return true;
	}

	return false;
}

bool BaseRandomShapeLayer::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	if (state != InputState::kDown)
		return false;

	switch (rand() % 4)
	{
	case 0:
		m_Shapes.push_back(std::make_unique<RandomRect>(x, y));
		break;

	case 1:
		m_Shapes.push_back(std::make_unique<RandomRRect>(x, y));
		break;

	case 2:
		m_Shapes.push_back(std::make_unique<RandomCircle>(x, y));
		break;

	default:
		m_Shapes.push_back(std::make_unique<RandomPath>(x, y));
		break;
	}

	return true;
}