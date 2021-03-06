#ifndef EXAMPLELAYER14_H_EEC9FE8C_EEE8_4524_9FF1_0793BCB5DBFE
#define EXAMPLELAYER14_H_EEC9FE8C_EEE8_4524_9FF1_0793BCB5DBFE

#include "BaseLayer.h"

class ExampleLayer14 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #14: Mask filters"; };
	void Draw(SkCanvas* canvas) override;
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override;
	bool ProcessMouseWheel(InputState state, ModifierKey modifiers) override;

protected:
	bool m_bEnableMask = true;
	SkScalar m_Radius = 5.f;
};

#endif // EXAMPLELAYER14_H_EEC9FE8C_EEE8_4524_9FF1_0793BCB5DBFE
