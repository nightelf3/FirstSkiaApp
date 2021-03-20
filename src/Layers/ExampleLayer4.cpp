#include "include/Layers/ExampleLayer4.h"

void ExampleLayer4::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);
	__super::Draw(canvas);
}