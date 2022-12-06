#include "include/Layers/LinearGradient4P.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"

LinearGradient4P::LinearGradient4P()
{
	const SkString str{R"---(
		uniform float2 size;
		half4 main(float2 p) {
			p = p / size;
			half3 color_top = mix(half3(1, 0, 0), half3(0, 1, 0), p.x);
			half3 color_bottom = mix(half3(0, 0, 1), half3(1, 1, 0), p.x);
			return mix(color_top, color_bottom, p.y).rgb1;
		}
	)---"};
	auto [effect, error] = SkRuntimeEffect::MakeForShader(str);
	m_Effect = effect;
}

void LinearGradient4P::onPaint(SkSurface* surface)
{
	SkCanvas* canvas = surface->getCanvas();
	if (m_Effect)
	{
		SkPaint paint;
		paint.setShader(m_Effect->makeShader(GetUniforms(canvas), {}, nullptr));
		canvas->drawPaint(paint);
	}
}

sk_sp<SkData> LinearGradient4P::GetUniforms(SkCanvas* canvas) const
{
	struct ShaderParams
	{
		SkScalar width;
		SkScalar height;
	};
	
	sk_sp<SkData> data = SkData::MakeUninitialized(sizeof(ShaderParams));
	if (ShaderParams* params = static_cast<ShaderParams*>(data->writable_data()))
	{
		const SkRect rect = SkRect::Make(canvas->getDeviceClipBounds());
		params->width = rect.width();
		params->height = rect.height();
	}

	return data;
}
