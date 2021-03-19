#ifndef EXAMPLELAYER2_H_DAC5D2A7_B370_42A9_9F7E_52CA5CA922A6
#define EXAMPLELAYER2_H_DAC5D2A7_B370_42A9_9F7E_52CA5CA922A6

#include "BaseLayer.h"

class ExampleLayer2 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #2: Draw a shape depends on window size"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // EXAMPLELAYER2_H_DAC5D2A7_B370_42A9_9F7E_52CA5CA922A6
