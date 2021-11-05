#include "include/Layers/Utils/Histogram.h"

#include "include/core/SkFont.h"

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

	Calculate(data, static_cast<size_t>(image->width()), static_cast<size_t>(image->height()));
	return true;
}

void Histogram::Draw(SkCanvas* canvas)
{
	m_FPS.Draw(canvas);
}

void Histogram::Calculate(sk_sp<SkData> data, size_t width, size_t height)
{
	m_FPS.Calc();

	THistogram& histogram = *m_Histogram;
	auto pixels = reinterpret_cast<const SkColor*>(data->bytes());
	auto pixelsEnd = pixels + width * height;
	for (; pixels != pixelsEnd; pixels++)
	{
		histogram[kRed_Channel][SkColorGetR(*pixels)]++;
		histogram[kGreen_Channel][SkColorGetG(*pixels)]++;
		histogram[kBlue_Channel][SkColorGetB(*pixels)]++;
	}

	for (size_t i = 0; i < kChannelSize; i++)
		histogram[kMaster_Channel][i] = histogram[kRed_Channel][i] + histogram[kGreen_Channel][i] + histogram[kBlue_Channel][i];

	m_FPS.Calc();
}