#pragma once

#include "include/effects/SkRuntimeEffect.h"

namespace Shaders
{
template<typename T>
sk_sp<SkShader> CreateShader(sk_sp<SkImage> image, sk_sp<SkRuntimeEffect> effect, T& params, const SkMatrix* localMatrix = nullptr, const SkMatrix* imageMatrix = nullptr)
{
	if (!effect)
		return nullptr;

	sk_sp<SkShader> pColorizerShader = image->makeShader(SkTileMode::kDecal, SkTileMode::kDecal, {}, imageMatrix);
	sk_sp<SkData> dataInput = SkData::MakeWithCopy(&params, sizeof(T));
	sk_sp<SkShader> children[] = { pColorizerShader };
	return effect->makeShader(dataInput, children, 1, localMatrix);
}

SkRuntimeEffect::Result LoadFromFile(const SkString& filePath);
}
