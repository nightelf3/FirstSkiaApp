#ifndef CUSTOMGRADIENT_H_8107E04F_C6B6_45C6_8775_79B01B485837
#define CUSTOMGRADIENT_H_8107E04F_C6B6_45C6_8775_79B01B485837

#include "BaseLayer.h"

class CustomGradient final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Custom gradient shader"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // CUSTOMGRADIENT_H_8107E04F_C6B6_45C6_8775_79B01B485837
