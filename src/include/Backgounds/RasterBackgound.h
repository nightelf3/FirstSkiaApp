#pragma once

#include "BaseBackgound.h"
#include <vector>

class RasterBackgound : public BaseBackgound
{
public:
	RasterBackgound(WHandle handle);
	~RasterBackgound() override;

	std::wstring GetName() const override { return L"Raster"; }
	sk_sp<SkSurface> CreateSurface(int widht, int height) override;
	void Destroy() override {}
	void SwapBuffers() override;

protected:
	std::vector<uint8_t> m_SurfaceMemory;
};
