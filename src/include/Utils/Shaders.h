#pragma once

#include "include/effects/SkRuntimeEffect.h"

namespace Shaders
{
struct BWParameters
{
	float red = 40.0f;
	float yellow = 60.0f;
	float green = 40.0f;
	float cyan = 60.0f;
	float blue = 20.0f;
	float magenta = 80.0f;
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
	return effect->makeShader(dataInput, children, 1, nullptr, false);
}

SkRuntimeEffect::Result LoadFromFile(const SkString& filePath);
}
