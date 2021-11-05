#pragma once

#include "include/core/SkImage.h"
#include "include/core/SkString.h"

SkRect GetBounds(SkCanvas* canvas);
sk_sp<SkImage> LoadImageFromFile(const SkString& filePath);

template<typename T>
T GetClamped(const T& v, const T& lo, const T& hi)
{
	return v < lo ? lo : hi < v ? hi : v;
}

bool IsPointInRect(SkScalar x, SkScalar y, const SkRect& rect);
