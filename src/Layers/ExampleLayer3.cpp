#include "include/Layers/ExampleLayer3.h"

void ExampleLayer3::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);
	__super::Draw(canvas);
}
