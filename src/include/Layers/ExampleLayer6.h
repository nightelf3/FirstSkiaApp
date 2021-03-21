#ifndef EXAMPLELAYER6_H_970915FC_FBAC_42CA_A6B0_B87DAF1327AB
#define EXAMPLELAYER6_H_970915FC_FBAC_42CA_A6B0_B87DAF1327AB

#include "BaseLayer.h"

class ExampleLayer6 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #6: Fixed unicode chars"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // EXAMPLELAYER6_H_970915FC_FBAC_42CA_A6B0_B87DAF1327AB
