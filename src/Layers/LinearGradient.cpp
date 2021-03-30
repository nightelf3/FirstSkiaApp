#include "include/Layers/LinearGradient.h"

#include "include/core/SkImage.h"
#include "include/effects/SkGradientShader.h"

void LinearGradient::Draw(SkCanvas* canvas)
{
	constexpr int nNumSteps = 256;

	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	SkColor colors[nNumSteps];
	SkColor4f color = SkColors::kYellow;
	for (int i = 0; i < nNumSteps; ++i)
	{
		color.fA = (float)i / nNumSteps;
		colors[i] = color.toSkColor();
	}

	SkPoint pts[2] = {
		SkPoint::Make(0, 0),
		SkPoint::Make(canvas->getDeviceClipBounds().width(), canvas->getDeviceClipBounds().height())
	};
	SkPaint paint;
	paint.setShader(SkGradientShader::MakeLinear(pts, colors, nullptr, nNumSteps, SkTileMode::kClamp));

	canvas->drawPaint(paint);
}