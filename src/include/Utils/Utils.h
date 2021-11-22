#pragma once

#include "include/core/SkImage.h"
#include "include/core/SkString.h"

SkRect GetBounds(SkCanvas* canvas);
sk_sp<SkImage> LoadImageFromFile(const SkString& filePath);

bool IsXInRect(SkScalar x, const SkRect& rect);
bool IsPointInRect(SkScalar x, SkScalar y, const SkRect& rect);
