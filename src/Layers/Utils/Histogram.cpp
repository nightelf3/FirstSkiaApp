#include "include/Layers/Utils/Histogram.h"

#include "include/core/SkFont.h"
#include <Windows.h>
namespace
{
	constexpr size_t kChannelSize = 256;
	constexpr size_t kChannelsCount = 4;
	constexpr size_t kHistogramSize = kChannelsCount * kChannelSize;

	constexpr size_t kMasterOffset = 0;
	constexpr size_t kRedOffset = kChannelSize;
	constexpr size_t kGreenOffset = kChannelSize * 2;
	constexpr size_t kBlueOffset = kChannelSize * 3;
}

Histogram::Histogram(sk_sp<SkImage> image)
{
	Initialize(std::move(image));
}

bool Histogram::Initialize(sk_sp<SkImage> image)
{
	if (!image || SkColorType::kBGRA_8888_SkColorType != image->imageInfo().colorType())
		return false;

	const size_t rowBytes = image->width() * SkColorTypeBytesPerPixel(SkColorType::kBGRA_8888_SkColorType);
	sk_sp<SkData> data = SkData::MakeUninitialized(rowBytes * image->height());
	SkImageInfo dstInfo = SkImageInfo::Make(image->width(), image->height(), SkColorType::kBGRA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
	if (!image->readPixels(nullptr, dstInfo, data->writable_data(), rowBytes, 0, 0))
		return false;

	Calc(data, static_cast<size_t>(image->width()), static_cast<size_t>(image->height()));
	return true;
}

void Histogram::Draw(SkCanvas* canvas)
{
	m_FPS.Draw(canvas);
}

void Histogram::Calc(sk_sp<SkData> data, size_t width, size_t height)
{
	m_FPS.Calc();

	auto pixels = reinterpret_cast<const SkColor*>(data->bytes());
	m_Histogram.resize(kHistogramSize, 0); // since we suport RGBA_8888 only
	for (size_t i = 0; i < height; i++, pixels += width)
	{
		for (size_t j = 0; j < width; j++)
		{
			const SkColor color = pixels[j];
			const uint16_t r = SkColorGetR(color);
			const uint16_t g = SkColorGetG(color);
			const uint16_t b = SkColorGetB(color);
			m_Histogram[kMasterOffset + (r + g + b) / 3]++;
			m_Histogram[kRedOffset + r]++;
			m_Histogram[kGreenOffset + g]++;
			m_Histogram[kBlueOffset + b]++;
		}
	}

	m_FPS.Calc();
}