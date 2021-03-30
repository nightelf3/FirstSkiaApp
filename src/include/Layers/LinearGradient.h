#ifndef LINEARGRADIENT_H_3F426028_73BB_4C1A_BA78_5A855A221310
#define LINEARGRADIENT_H_3F426028_73BB_4C1A_BA78_5A855A221310

#include "BaseLayer.h"

class LinearGradient final : public BaseLayer
{
public:
	std::wstring GetTitle() const override { return L"Linear gradient shader"; };
	void Draw(SkCanvas* canvas) override;
};

#endif // LINEARGRADIENT_H_3F426028_73BB_4C1A_BA78_5A855A221310
