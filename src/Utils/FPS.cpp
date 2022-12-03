#include "include/Utils/FPS.h"
#include "include/core/SkFont.h"
#include "include/core/SkCanvas.h"

using namespace std::chrono;
namespace
{
	using TimeType = nanoseconds;
	constexpr double period = static_cast<double>(TimeType::period::den);
}

void FPS::Calc()
{
	const time_point<system_clock> now = system_clock::now();
	m_FPS = period / std::max(duration_cast<TimeType>(now - m_LastCalc).count(), 1ll);
	m_LastCalc = now;
}

void FPS::Draw(SkCanvas* canvas)
{
	const SkString sFPS = Get();

	SkPaint paint;
	paint.setColor(SkColors::kWhite);

	SkFont font;
	font.setSize(20);

	SkRect measure;
	font.measureText(sFPS.c_str(), strlen(sFPS.c_str()), SkTextEncoding::kUTF8, &measure);

	canvas->drawString(sFPS.c_str(), 5, measure.height(), font, paint);
}

SkString FPS::Get() const
{
	SkString sFPS;
	sFPS.printf("FPS: %.3f", m_FPS);
	return sFPS;
}
