#include "include/Layers/Utils/FPS.h"
#include "include/core/SkFont.h"

using namespace std::chrono;
namespace
{
	using TimeType = nanoseconds;
	constexpr double period = static_cast<double>(TimeType::period::den);
}

void FPS::DrawFPS(SkCanvas* canvas)
{
	const time_point<system_clock> now = system_clock::now();
	const double fps = period / std::max(duration_cast<TimeType>(now - m_LastDraw).count(), 60ll);

	char sFPS[64]{};
	sprintf_s(sFPS, "FPS: %.3f", fps);

	SkPaint paint;
	paint.setColor(SkColors::kWhite);

	SkFont font;
	font.setSize(20);

	SkRect measure;
	font.measureText(sFPS, strlen(sFPS), SkTextEncoding::kUTF8, &measure);

	canvas->drawSimpleText(sFPS, strlen(sFPS), SkTextEncoding::kUTF8, 5, measure.height(), font, paint);

	m_LastDraw = now;
}
