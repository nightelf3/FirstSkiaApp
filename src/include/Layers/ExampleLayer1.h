#ifndef EXAMPLELAYER1_H_8107E04F_C6B6_45C6_8775_79B01B485837
#define EXAMPLELAYER1_H_8107E04F_C6B6_45C6_8775_79B01B485837

#include "BaseLayer.h"

class ExampleLayer1 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #1: Draw a simple shape"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // EXAMPLELAYER1_H_8107E04F_C6B6_45C6_8775_79B01B485837
