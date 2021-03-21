#include "include/Layers/ExampleLayer12.h"
#include "include/effects/SkPerlinNoiseShader.h"

void ExampleLayer12::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	SkPaint paint;
	paint.setShader(SkPerlinNoiseShader::MakeFractalNoise(0.05f, 0.05f, 4, 0.0f, nullptr));
	canvas->drawPaint(paint);
}