#ifndef EXAMPLELAYER8_H_C985A449_00CF_471A_A900_DCFBEF2BD482
#define EXAMPLELAYER8_H_C985A449_00CF_471A_A900_DCFBEF2BD482

#include "BaseLayer.h"

class ExampleLayer8 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #8: Draw rotated shapes"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // EXAMPLELAYER8_H_C985A449_00CF_471A_A900_DCFBEF2BD482
