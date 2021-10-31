#pragma once

#include "BaseLayer.h"

class ExampleLayer final : public BaseLayer
{
public:
	ExampleLayer();
	std::wstring GetTitle() const override { return L"Example"; };
	void Draw(SkCanvas* canvas) override;

private:
	sk_sp<SkImage> m_Image;
};
