#include "include/Layers/ThankYouLayer.h"
#include "include/Layers/Utils/Utils.h"
#include "include/core/SkFont.h"
#include "include/effects/SkGradientShader.h"
#include "include/effects/SkPerlinNoiseShader.h"

using namespace std::chrono;

ThankYouLayer::ThankYouLayer()
{
	SkString path;
	for (size_t i = 0; i < m_Images.size(); i++)
	{
		path.printf("resources/dance_%d.gif", i);
		m_Images[i] = LoadImageFromFile(path);
	}
}

void ThankYouLayer::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);
	const SkRect canvasBounds = GetBounds(canvas);

	time_point<system_clock> now = system_clock::now();
	if ((now - m_LastDraw) > 150ms)
	{
		m_Current = (m_Current + 1) % m_Images.size();
		m_LastDraw = now;
	}

	const SkIRect imageBounds = m_Images[m_Current]->bounds();
	canvas->drawImage(m_Images[m_Current], (canvasBounds.width() - imageBounds.width()) / 2.f, (canvasBounds.height() - imageBounds.height()) / 2.f, {});

	SkPaint paint;
	paint.setAntiAlias(true);

	static SkScalar offset = 0;
	const SkPoint points[2] = { SkPoint::Make(offset, offset), SkPoint::Make(256.0f + offset, 256.0f + offset) };
	const SkColor colors[2] = { SkColorSetRGB(66, 133, 244), SkColorSetRGB(15, 157, 88) };
	paint.setShader(SkShaders::Blend(
		SkBlendMode::kDifference,
		SkGradientShader::MakeLinear(points, colors, nullptr, 2, SkTileMode::kClamp, 0, nullptr),
		SkPerlinNoiseShader::MakeTurbulence(0.025f + offset / 1000.f, 0.025f + offset / 1000.f, 2, 0.0f, nullptr)));
	offset = std::fmodf(offset + rand() % 10, 100.f);

	const char str[] = "Thank you!!!";
	SkFont font(nullptr, 100.f);
	SkRect textBounds;
	font.measureText(str, strlen(str), SkTextEncoding::kUTF8, &textBounds, &paint);
	canvas->drawString(str, (canvasBounds.width() - textBounds.width()) / 2.f, (canvasBounds.height() - textBounds.height()) / 2.f - imageBounds.height() / 2.f, font, paint);
}