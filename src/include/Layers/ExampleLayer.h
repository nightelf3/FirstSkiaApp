#ifndef EXAMPLELAYER0_H_40FC2ED3_321B_4018_ACE0_C45D5681E708
#define EXAMPLELAYER0_H_40FC2ED3_321B_4018_ACE0_C45D5681E708

#include "BaseLayer.h"

class ExampleLayer final : public BaseLayer
{
public:
	ExampleLayer();
	std::wstring GetTitle() const override { return L"Example"; };
	void Draw(SkCanvas* canvas) override;

private:
	sk_sp<SkImage> m_Image;
};

#endif // EXAMPLELAYER0_H_40FC2ED3_321B_4018_ACE0_C45D5681E708
