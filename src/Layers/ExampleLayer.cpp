#include "include/Layers/ExampleLayer.h"
#include "include/Layers/Utils/Utils.h"

ExampleLayer::ExampleLayer()
{
	m_Image = LoadImageFromFile(SkString("resources/8k.jpg"));
}

void ExampleLayer::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	{  // draw the image
		const SkRect bounds = GetBounds(canvas);
		const SkScalar ratio = static_cast<SkScalar>(m_Image->width()) / m_Image->height();
		const SkScalar width = ratio >= 1.0f ? bounds.width() : bounds.height() * ratio;
		const SkScalar height = ratio >= 1.0f ? bounds.width() / ratio : bounds.height();

		SkAutoCanvasRestore guard(canvas, true);
		canvas->scale(width / m_Image->width(), height / m_Image->height());

		canvas->drawImage(m_Image, 0, 0);
	}
}