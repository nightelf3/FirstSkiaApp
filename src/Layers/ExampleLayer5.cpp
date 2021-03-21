#include "include/Layers/ExampleLayer5.h"
#include "include/core/SkFont.h"
#include "include/core/SkFontMgr.h"

namespace
{
	const char sDefaultFamily[] = "Default";
	const std::vector<std::wstring> sText = {
		L"一 (yī) – “one”",
		L"二 (èr) – “two”",
		L"三 (sān) – “three”",
		L"四 (sì) – “four”",
		L"五 (wǔ) – “five”",
		L"六 (liù) – “six”",
		L"七 (qī) – “seven",
		L"八 (bā) – “eight”",
		L"九 (jiǔ) – “nine”",
		L"十 (shí) – “ten”",
		L"文言文 - wényánwén",
		L"白话文 - Báihuà Wén",
		L"貞 zhēn became 贞 zhēn",
		L"贈 zèng became 赠 zèng"
	};

	template<typename TChar>
	SkScalar DrawAndMeatureString(SkCanvas* canvas, const TChar str[], const size_t lenght, const SkFont& font, const SkPaint& paint, SkScalar x, SkScalar y)
	{
		const auto encoding = sizeof(TChar) == 1 ? SkTextEncoding::kUTF8 : SkTextEncoding::kUTF16;
		SkRect measure;
		font.measureText(str, lenght * sizeof(TChar), encoding, &measure);
		canvas->drawSimpleText(str, lenght * sizeof(TChar), encoding, x, y, font, paint);
		return measure.height() + font.getSize() / 4.f;
	}

	void DrawSkText(SkCanvas* canvas, const std::vector<std::wstring>& sText, const char familyName[], SkScalar x, SkScalar y, const SkPaint& paint)
	{
		sk_sp<SkFontMgr> fontManager = SkFontMgr::RefDefault();
		sk_sp<SkTypeface> typeface(fontManager->matchFamilyStyle(familyName, {}));
		SkFont font(typeface, 20);

		if (!familyName)
			familyName = sDefaultFamily;

		y += DrawAndMeatureString(canvas, familyName, strlen(familyName), font, paint, x, y);
		for (auto& str : sText)
			y += DrawAndMeatureString(canvas, str.c_str(), str.length(), font, paint, x, y);
	}
}

void ExampleLayer5::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	SkPaint paint;
	paint.setColor(SkColors::kWhite);
	DrawSkText(canvas, sText, nullptr, 100, 100, paint);

	paint.setColor(SkColors::kGreen);
	DrawSkText(canvas, sText, "Yu Gothic UI", 400, 100, paint);
}