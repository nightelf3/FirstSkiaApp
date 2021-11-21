#include "include/Utils/Utils.h"
#include "include/core/SkCanvas.h"

SkRect GetBounds(SkCanvas* canvas)
{
	SkRect rect;
	rect.set(canvas->getDeviceClipBounds());
	return rect;
}

sk_sp<SkImage> LoadImageFromFile(const SkString& filePath)
{
	sk_sp<SkData> skData = SkData::MakeFromFileName(filePath.c_str());
	if (!skData)
		return nullptr;

	return SkImage::MakeFromEncoded(std::move(skData));
}

bool IsPointInRect(SkScalar x, SkScalar y, const SkRect& rect)
{
	return rect.left() <= x && x <= rect.right() && rect.top() <= y && y <= rect.bottom();
}
