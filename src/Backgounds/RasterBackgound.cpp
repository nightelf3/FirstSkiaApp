#include "include/Backgounds/RasterBackgound.h"
#include <Windows.h>

RasterBackgound::RasterBackgound(WHandle handle) :
	BaseBackgound(handle)
{
}

RasterBackgound::~RasterBackgound()
{
	Destroy();
}

sk_sp<SkSurface> RasterBackgound::CreateSurface(int widht, int height)
{
	const size_t bmpSize = sizeof(BITMAPINFOHEADER) + widht * height * sizeof(uint32_t);
	m_SurfaceMemory.resize(bmpSize);

	BITMAPINFO* bmpInfo = reinterpret_cast<BITMAPINFO*>(m_SurfaceMemory.data());
	ZeroMemory(bmpInfo, sizeof(BITMAPINFO));
	bmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo->bmiHeader.biWidth = widht;
	bmpInfo->bmiHeader.biHeight = -height; // negative means top-down bitmap. Skia draws top-down.
	bmpInfo->bmiHeader.biPlanes = 1;
	bmpInfo->bmiHeader.biBitCount = 32;
	bmpInfo->bmiHeader.biCompression = BI_RGB;
	void* pixels = bmpInfo->bmiColors;

	SkImageInfo info = SkImageInfo::Make(widht, height, SkColorType::kBGRA_8888_SkColorType, kPremul_SkAlphaType);
	return SkSurface::MakeRasterDirect(info, pixels, sizeof(uint32_t) * widht);
}

void RasterBackgound::SwapBuffers()
{
	if (m_SurfaceMemory.empty())
		return;

	BITMAPINFO* bmpInfo = reinterpret_cast<BITMAPINFO*>(m_SurfaceMemory.data());
	HDC dc = GetDC(m_WHandle);
	StretchDIBits(dc, 0, 0, bmpInfo->bmiHeader.biWidth, -bmpInfo->bmiHeader.biHeight, 0, 0,
		bmpInfo->bmiHeader.biWidth, -bmpInfo->bmiHeader.biHeight, bmpInfo->bmiColors,
		bmpInfo, DIB_RGB_COLORS, SRCCOPY);
	ReleaseDC(m_WHandle, dc);
}