#ifndef EXAMPLELAYER0_H_40FC2ED3_321B_4018_ACE0_C45D5681E708
#define EXAMPLELAYER0_H_40FC2ED3_321B_4018_ACE0_C45D5681E708

#include "BaseLayer.h"

class ExampleLayer0 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #0: Empty PlatformWindow"; };
	void Draw(SkCanvas* canvas) override { canvas->clear(SkColors::kBlack); }
};

#endif // EXAMPLELAYER0_H_40FC2ED3_321B_4018_ACE0_C45D5681E708
