#include "include/Utils/Utils.h"
#include "include/core/SkCanvas.h"

SkRect Utils::GetBounds(SkCanvas* canvas)
{
	SkRect rect;
	rect.set(canvas->getDeviceClipBounds());
	return rect;
}

sk_sp<SkImage> Utils::LoadImageFromFile(const SkString& filePath)
{
	sk_sp<SkData> skData = SkData::MakeFromFileName(filePath.c_str());
	if (!skData)
		return nullptr;

	return SkImage::MakeFromEncoded(std::move(skData));
}

bool Utils::IsXInRect(SkScalar x, const SkRect& rect)
{
	return rect.left() <= x && x <= rect.right();
}

bool Utils::IsPointInRect(SkScalar x, SkScalar y, const SkRect& rect)
{
	return rect.left() <= x && x <= rect.right() && rect.top() <= y && y <= rect.bottom();
}
