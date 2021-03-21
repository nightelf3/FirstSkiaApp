#ifndef EXAMPLELAYER15_H_6C3829EA_668C_4C17_B265_2319E1ABA583
#define EXAMPLELAYER15_H_6C3829EA_668C_4C17_B265_2319E1ABA583

#include "BaseLayer.h"

class ExampleLayer15 final : public BaseLayer
{
public:
	ExampleLayer15();
	std::wstring GetTitle() const override { return L"Example #15: Color filters"; };
	void Draw(SkCanvas* canvas) override;

private:
	sk_sp<SkImage> m_Image;
};

#endif // EXAMPLELAYER15_H_6C3829EA_668C_4C17_B265_2319E1ABA583
