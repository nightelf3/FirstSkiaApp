#ifndef EXAMPLELAYER9_H_2542A75B_0224_4BA9_A3A8_1A5D07271C40
#define EXAMPLELAYER9_H_2542A75B_0224_4BA9_A3A8_1A5D07271C40

#include "BaseLayer.h"

class ExampleLayer9 final : public BaseLayer
{
public:
	ExampleLayer9();
	std::wstring GetTitle() const override { return L"Example #9: Draw transformed bitmap"; };
	void Draw(SkCanvas* canvas) override;
	bool ProcessKey(Key key, InputState state, ModifierKey modifiers) override;
	bool ProcessMouseWheel(InputState state, ModifierKey modifiers) override;

private:
	sk_sp<SkImage> m_Image;
	SkMatrix m_Matrix;
};

#endif // EXAMPLELAYER9_H_2542A75B_0224_4BA9_A3A8_1A5D07271C40
