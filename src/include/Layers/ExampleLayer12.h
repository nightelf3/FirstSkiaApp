#ifndef EXAMPLELAYER12_H_E746D430_1D0C_4287_B251_76710336D44E
#define EXAMPLELAYER12_H_E746D430_1D0C_4287_B251_76710336D44E

#include "BaseLayer.h"

class ExampleLayer12 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #12: Fractal shader"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // EXAMPLELAYER12_H_E746D430_1D0C_4287_B251_76710336D44E
