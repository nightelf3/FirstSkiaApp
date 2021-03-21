#ifndef EXAMPLELAYER10_H_CF668516_079E_4652_9E01_5ACB2F08554F
#define EXAMPLELAYER10_H_CF668516_079E_4652_9E01_5ACB2F08554F

#include "BaseLayer.h"

class ExampleLayer10 final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #10: Blend modes"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // EXAMPLELAYER10_H_CF668516_079E_4652_9E01_5ACB2F08554F
