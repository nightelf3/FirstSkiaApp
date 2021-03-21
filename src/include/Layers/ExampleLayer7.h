#ifndef EXAMPLELAYER7_H_5F99114A_F7E9_4432_B150_E4AE87CC1F12
#define EXAMPLELAYER7_H_5F99114A_F7E9_4432_B150_E4AE87CC1F12

#include "BaseLayer.h"

class ExampleLayer7 final : public BaseLayer
{
public:
	ExampleLayer7();

	std::wstring GetTitle() const override { return L"Example #7: Load bitmap"; };
	void Draw(SkCanvas* canvas) override;

	bool ProcessKey(Key key, InputState state, ModifierKey modifiers) override;

private:
	sk_sp<SkImage> m_Image;
	SkPoint m_Point;
};

#endif // EXAMPLELAYER7_H_5F99114A_F7E9_4432_B150_E4AE87CC1F12
