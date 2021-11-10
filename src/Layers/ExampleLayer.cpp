#include "include/Layers/ExampleLayer.h"
#include "include/Layers/Utils/Utils.h"
#include "include/Controls/Slider.h"

namespace
{
	constexpr SkScalar kPanelSize = 300.0f;  // in px
	constexpr SkScalar kPanelPadding = 10.0f;  // in px

	SkRect GetPanelRect(SkRect bounds)
	{
		bounds.fLeft = bounds.fRight - kPanelSize;
		return bounds.makeInset(kPanelPadding, kPanelPadding);
	}
}

ExampleLayer::ExampleLayer()
{
	m_Image = LoadImageFromFile(SkString("resources/8k.jpg"));
	m_RotateSlider = m_Container.AddControl<Slider>(SkString{"Rotate:"});\
}

void ExampleLayer::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	const SkRect bounds = GetBounds(canvas);
	{  // draw the image
		SkAutoCanvasRestore guard(canvas, true);
		const SkRect imageRect = SkRect::MakeWH(m_Image->width(), m_Image->height());
		SkMatrix matrix = SkMatrix::RectToRect(imageRect, bounds, SkMatrix::kCenter_ScaleToFit);
		matrix.postRotate(m_RotateSlider.lock()->GetValue() * 360.0f, bounds.centerX(), bounds.centerY());
		canvas->setMatrix(matrix);
		canvas->drawImage(m_Image, 0.0f, 0.0f);
	}

	// draw controls
	m_Container.Draw(canvas, GetPanelRect(bounds));
}

bool ExampleLayer::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	return m_Container.ProcessMouse(x, y, state, modifiers);
}