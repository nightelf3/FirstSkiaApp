#ifndef EXAMPLELAYER7_H_5F99114A_F7E9_4432_B150_E4AE87CC1F12
#define EXAMPLELAYER7_H_5F99114A_F7E9_4432_B150_E4AE87CC1F12

#include "BaseLayer.h"

class ExampleLayer7 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #7: Load bitmap"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // EXAMPLELAYER7_H_5F99114A_F7E9_4432_B150_E4AE87CC1F12
