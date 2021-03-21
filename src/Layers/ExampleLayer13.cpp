#include "include/Layers/ExampleLayer13.h"
#include "include/Layers/Utils/Utils.h"
#include "include/effects/SkGradientShader.h"
#include "include/effects/SkPerlinNoiseShader.h"

void ExampleLayer13::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	const SkRect rBounds = GetBounds(canvas);
	SkColor colors[2] = {SK_ColorBLUE, SK_ColorYELLOW};
	SkPaint paint;
	paint.setShader(SkShaders::Blend(
		SkBlendMode::kDifference,
		SkGradientShader::MakeRadial(SkPoint::Make(rBounds.centerX(), rBounds.centerY()), std::min(rBounds.centerX(), rBounds.centerY()),
			colors, nullptr, 2, SkTileMode::kClamp, 0, nullptr),
		SkPerlinNoiseShader::MakeTurbulence(0.025f, 0.025f, 2, 0.0f, nullptr)));
	canvas->drawPaint(paint);
}
