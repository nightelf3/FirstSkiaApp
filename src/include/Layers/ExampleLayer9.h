#ifndef EXAMPLELAYER9_H_2542A75B_0224_4BA9_A3A8_1A5D07271C40
#define EXAMPLELAYER9_H_2542A75B_0224_4BA9_A3A8_1A5D07271C40

#include "BaseLayer.h"

class ExampleLayer9 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #9: Draw transformed bitmap"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // EXAMPLELAYER9_H_2542A75B_0224_4BA9_A3A8_1A5D07271C40
