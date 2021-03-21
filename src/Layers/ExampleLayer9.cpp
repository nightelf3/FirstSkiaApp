#include "include/Layers/ExampleLayer9.h"
#include "include/Layers/Utils/Utils.h"
#include "include/core/SkMatrix.h"

ExampleLayer9::ExampleLayer9()
{
	m_Image = LoadImageFromFile(SkString("resources/doge.png"));
	m_Matrix.setIdentity();
}

void ExampleLayer9::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	SkAutoCanvasRestore checkpoint(canvas, true);
	canvas->setMatrix(m_Matrix);
	canvas->drawImage(m_Image, 200, 200);
}

bool ExampleLayer9::ProcessKey(Key key, InputState state, ModifierKey modifiers)
{
	constexpr SkScalar increment = 10.f;
	switch (key)
	{
	case Key::kUp:
		m_Matrix.preTranslate(0, -increment);
		return true;

	case Key::kRight:
		m_Matrix.preTranslate(increment, 0);
		return true;

	case Key::kDown:
		m_Matrix.preTranslate(0, increment);
		return true;

	case Key::kLeft:
		m_Matrix.preTranslate(-increment, 0);
		return true;
	}
	return false;
}

bool ExampleLayer9::ProcessMouseWheel(InputState state, ModifierKey modifiers)
{
	if (ModifierKey::kNone == modifiers)
	{
		if (InputState::kZoomIn == state)
			m_Matrix.preScale(1.1, 1.1);
		else
			m_Matrix.preScale(0.9, 0.9);
		return true;
	}
	else if (ModifierKey::kShift == modifiers)
	{
		if (InputState::kZoomIn == state)
			m_Matrix.preSkew(0.1, 0);
		else
			m_Matrix.preSkew(-0.1, 0);
		return true;
	}
	else
	{
		if (InputState::kZoomIn == state)
			m_Matrix.preSkew(0, 0.1);
		else
			m_Matrix.preSkew(0, -0.1);
		return true;
	}

	return false;
}