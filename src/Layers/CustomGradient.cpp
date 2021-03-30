#include "include/Layers/CustomGradient.h"

#include "include/core/SkImage.h"
#include "include/effects/SkRuntimeEffect.h"

static const std::string LINEAR_GRAD_SHADER = R"---(
	uniform shader colorizer;
	uniform float colorCount;
	uniform float2 pt1;
	uniform float2 pt2;
	uniform float l;
	half4 main(float2 p) {
		float2 v1 = p - pt1;
		float2 v2 = pt2 - pt1;
		float t = dot(v1, v2)/l;
		t = clamp(t, 0.0, 1.0);
		float2 colorPos = float2(floor(colorCount*t) + 0.5, 0.0);
		return sample(colorizer, colorPos);
	})---";

void CustomGradient::Draw(SkCanvas* canvas)
{
	constexpr int nNumSteps = 256;

	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	const SkImageInfo info = SkImageInfo::Make(nNumSteps, 1, SkColorType::kBGRA_8888_SkColorType, kPremul_SkAlphaType);
	SkBitmap bmp;
	bmp.allocPixels(info);
	uint32_t* pixels32 = reinterpret_cast<uint32_t*>(bmp.getPixels());
	SkColor4f color = SkColors::kYellow;
	for (int i = 0; i < nNumSteps; ++i)
	{
		color.fA = (float)i / nNumSteps;
		pixels32[i] = color.toSkColor();
	}
	bmp.setImmutable();

	sk_sp<SkImage> pSkImage = SkImage::MakeFromBitmap(bmp);
	sk_sp<SkShader> pColorizerShader = pSkImage->makeShader(SkTileMode::kClamp, SkTileMode::kClamp, {}, SkMatrix::I());

	auto effect = SkRuntimeEffect::Make(SkString(LINEAR_GRAD_SHADER.c_str()));
	auto error = effect.errorText.c_str();

	struct {
		float colorCount = 0;
		float pt1[2];
		float pt2[2];
		float l;
	} fInput;
	fInput.colorCount = static_cast<float>(nNumSteps);
	fInput.pt1[0] = 0;
	fInput.pt1[1] = 0;
	fInput.pt2[0] = canvas->getDeviceClipBounds().width();
	fInput.pt2[1] = canvas->getDeviceClipBounds().height();
	fInput.l = powf(fInput.pt2[0] - fInput.pt1[0], 2) + powf(fInput.pt2[1] - fInput.pt2[0], 2);

	auto dataInput = SkData::MakeWithCopy(&fInput, sizeof(fInput));
	sk_sp<SkShader> children[] = { pColorizerShader };

	SkPaint paint;
	paint.setShader(effect.effect->makeShader(
		/*uniforms=*/    dataInput,
		/*children=*/    children,
		/*childCount=*/  1,
		/*localMatrix=*/ nullptr,
		/*isOpaque=*/    false));

	canvas->drawPaint(paint);
}