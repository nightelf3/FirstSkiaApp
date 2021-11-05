#pragma once

#include "include/core/SkImage.h"
#include "FPS.h"
#include <vector>

class Histogram
{
public:
	enum Channles : size_t
	{
		kMaster_Channel = 0,
		kRed_Channel,
		kGreen_Channel,
		kBlue_Channel
	};

	Histogram(sk_sp<SkImage> image);
	bool Initialize(sk_sp<SkImage> image);

	void Draw(SkCanvas* canvas);

private:
	void Calculate(sk_sp<SkData> data, size_t width, size_t height);

	static constexpr size_t kChannelSize = 256;
	static constexpr size_t kChannelsCount = 4;
	using THistogram = std::array<std::array<size_t, kChannelSize>, kChannelsCount>;
	std::unique_ptr<THistogram> m_Histogram = std::make_unique<THistogram>();
	FPS m_FPS;  //TODO: implement another class
};