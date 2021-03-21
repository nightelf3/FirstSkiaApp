#ifndef EXAMPLELAYER11_H_E746D430_1D0C_4287_B251_76710336D44E
#define EXAMPLELAYER11_H_E746D430_1D0C_4287_B251_76710336D44E

#include "BaseLayer.h"

class ExampleLayer11 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #11: Gradient shader"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // EXAMPLELAYER11_H_E746D430_1D0C_4287_B251_76710336D44E
