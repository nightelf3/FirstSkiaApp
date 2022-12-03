#pragma once

#include "include/effects/SkRuntimeEffect.h"

namespace Shaders
{
struct BWParameters
{
	float red = 0.4f;
	float yellow = 0.6f;
	float green = 0.4f;
	float cyan = 0.6f;
	float blue = 0.2f;
	float magenta = 0.8f;
};
constexpr BWParameters kBWDefault;

struct SwirlParameters
{
	float width = 0.0f;
	float height = 0.0f;
	float x = 0.5f;
	float y = 0.5f;
	float radius = 0.75f;
	float twist = 0.0f;
};
constexpr SwirlParameters kSwirlDefault;

template<typename T>
sk_sp<SkShader> CreateShader(sk_sp<SkImage> image, sk_sp<SkRuntimeEffect> effect, T& params)
{
	if (!effect)
		return nullptr;

	sk_sp<SkShader> pColorizerShader = image->makeShader(SkTileMode::kDecal, SkTileMode::kDecal, {}, SkMatrix::I());
	sk_sp<SkData> dataInput = SkData::MakeWithCopy(&params, sizeof(BWParameters));
	sk_sp<SkShader> children[] = { pColorizerShader };
	return effect->makeShader(dataInput, children, 1, nullptr);
}

SkRuntimeEffect::Result LoadFromFile(const SkString& filePath);
}
