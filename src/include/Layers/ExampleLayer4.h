#ifndef EXAMPLELAYER4_H_420BD2A9_ED0B_4F15_95AC_39D749018DA5
#define EXAMPLELAYER4_H_420BD2A9_ED0B_4F15_95AC_39D749018DA5

#include "Utils/RandomShapes.h"
#include "Utils/FPS.h"

class ExampleLayer4 final : public BaseRandomShapeLayer
{
public:
	std::wstring GetTitle() const override { return L"Example #4: Draw FPS for random shapes"; };
	void Draw(SkCanvas* canvas) override;

private:
	FPS m_FPS;
};

#endif // EXAMPLELAYER4_H_420BD2A9_ED0B_4F15_95AC_39D749018DA5
