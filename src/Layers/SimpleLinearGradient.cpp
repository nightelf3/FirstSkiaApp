#include "include/Layers/SimpleLinearGradient.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"

SimpleLinearGradient::SimpleLinearGradient()
{
	const SkString str{R"---(
		const float width = 1200;
		half4 main(float2 p) {
			return mix(half3(0, 0, 0), half3(1, 1, 1), p.x / width).rgb1;
		}
	)---"};
	auto [effect, error] = SkRuntimeEffect::MakeForShader(str);
	m_Effect = effect;
}

void SimpleLinearGradient::onPaint(SkSurface* surface)
{
	SkCanvas* canvas = surface->getCanvas();
	if (m_Effect)
	{
		SkPaint paint;
		paint.setShader(m_Effect->makeShader({}, {}, nullptr));
		canvas->drawPaint(paint);
	}
}
