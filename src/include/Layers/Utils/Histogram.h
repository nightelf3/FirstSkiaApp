#pragma once

#include "include/core/SkImage.h"
#include "FPS.h"
#include <vector>

class Histogram
{
public:
	Histogram(sk_sp<SkImage> image);
	bool Initialize(sk_sp<SkImage> image);

	void Draw(SkCanvas* canvas);

private:
	void Calc(sk_sp<SkData> data, size_t width, size_t height);

	std::vector<size_t> m_Histogram;
	FPS m_FPS;  //TODO: implement another class
};