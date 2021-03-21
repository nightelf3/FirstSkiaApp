#include "include/Layers/ExampleLayer11.h"
#include "include/core/SkPath.h"
#include "include/effects/SkGradientShader.h"
#include "include/effects/SkDiscretePathEffect.h"

void ExampleLayer11::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setPathEffect(SkDiscretePathEffect::Make(10.0f, 4.0f));

	SkPoint points[2] = { SkPoint::Make(0.0f, 0.0f), SkPoint::Make(356.0f, 356.0f) };
	SkColor colors[2] = { SkColorSetRGB(66, 133, 244), SkColorSetRGB(15, 157, 88) };
	paint.setShader(SkGradientShader::MakeLinear(points, colors, nullptr, 2, SkTileMode::kClamp, 0, nullptr));

	const SkScalar R = 200.0f, C = 428.0f;
	SkPath path;
	path.moveTo(C + R, C);
	for (int i = 1; i < 15; i++)
	{
		SkScalar a = 0.44879895f * i;
		SkScalar r = R + R * (i % 2);
		path.lineTo(C + r * cos(a), C + r * sin(a));
	}
	canvas->drawPath(path, paint);
}