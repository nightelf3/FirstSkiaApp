#include "include/Layers/ExampleLayer7.h"
#include "include/Layers/Utils/Utils.h"

ExampleLayer7::ExampleLayer7()
{
	m_Image = LoadImageFromFile(SkString("resources/doge.png"));
	m_Point = SkPoint::Make(-80, 600);
}

void ExampleLayer7::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	canvas->drawImage(m_Image, m_Point.x(), m_Point.y());
}

bool ExampleLayer7::ProcessKey(Key key, InputState state, ModifierKey modifiers)
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