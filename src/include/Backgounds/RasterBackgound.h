#ifndef RASTERBACKGROUND_H_5CCB585C_8D82_46B0_B5CB_AC74862E5EFF
#define RASTERBACKGROUND_H_5CCB585C_8D82_46B0_B5CB_AC74862E5EFF

#include "BaseBackgound.h"
#include <vector>

class RasterBackgound : public BaseBackgound
{
public:
	RasterBackgound(WHandle handle);
	~RasterBackgound();

	std::wstring GetName() const override { return L"Raster"; }
	sk_sp<SkSurface> CreateSurface(int widht, int height) override;
	void Destroy() override {}
	void SwapBuffers() override;

protected:
	std::vector<uint8_t> m_SurfaceMemory;
};

#endif // RASTERBACKGROUND_H_5CCB585C_8D82_46B0_B5CB_AC74862E5EFF
