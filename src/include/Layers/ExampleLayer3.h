#ifndef EXAMPLELAYER3_H_F0693353_488C_432D_A3D9_D0B3E3BFCD9B
#define EXAMPLELAYER3_H_F0693353_488C_432D_A3D9_D0B3E3BFCD9B

#include "BaseLayer.h"
#include "RandomShapes.h"

class ExampleLayer3 final : public BaseRandomShapeLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #3: Draw random shapes on click"; };
	void Draw(SkCanvas* canvas);
};

#endif // EXAMPLELAYER3_H_F0693353_488C_432D_A3D9_D0B3E3BFCD9B
