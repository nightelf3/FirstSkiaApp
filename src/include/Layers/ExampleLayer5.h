#ifndef EXAMPLELAYER5_H_8ACC9F3E_5B94_4885_90BE_C434ADD1F0BF
#define EXAMPLELAYER5_H_8ACC9F3E_5B94_4885_90BE_C434ADD1F0BF

#include "BaseLayer.h"

class ExampleLayer5 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #5: Draw unicode chars"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // EXAMPLELAYER5_H_8ACC9F3E_5B94_4885_90BE_C434ADD1F0BF
