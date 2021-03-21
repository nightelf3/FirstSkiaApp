#ifndef UTILS_H_904B28E0_5868_478E_AF22_AE0EDD9712F3
#define UTILS_H_904B28E0_5868_478E_AF22_AE0EDD9712F3

#include "include/core/SkImage.h"
#include "include/core/SkString.h"

SkRect GetBounds(SkCanvas* canvas);
sk_sp<SkImage> LoadImageFromFile(const SkString& filePath);

#endif // UTILS_H_904B28E0_5868_478E_AF22_AE0EDD9712F3
