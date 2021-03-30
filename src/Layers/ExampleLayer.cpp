#include "include/Layers/ExampleLayer.h"
#include "include/Layers/Utils/Utils.h"

ExampleLayer::ExampleLayer()
{
	m_Image = LoadImageFromFile(SkString("resources/doge.png"));
}

void ExampleLayer::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	// draw the image
	canvas->drawImage(m_Image, -80, 600);
}