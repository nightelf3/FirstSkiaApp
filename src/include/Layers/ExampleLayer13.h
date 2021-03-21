#ifndef EXAMPLELAYER13_H_4CECAE53_5910_44EE_B4BC_A23B8430030C
#define EXAMPLELAYER13_H_4CECAE53_5910_44EE_B4BC_A23B8430030C

#include "BaseLayer.h"

class ExampleLayer13 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #13: Combined shaders"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // EXAMPLELAYER13_H_4CECAE53_5910_44EE_B4BC_A23B8430030C
