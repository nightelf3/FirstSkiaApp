#include "include/Layers/ExampleLayer6.h"
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
	SkScalar DrawAndMeatureString(SkCanvas* canvas, const TChar str[], const size_t lenght, SkFont& font, const SkPaint& paint, SkScalar x, SkScalar y, bool bFixTypeface)
	{
		const auto encoding = sizeof(TChar) == 1 ? SkTextEncoding::kUTF8 : SkTextEncoding::kUTF16;
		SkScalar height = 0;
		sk_sp<SkFontMgr> fontManager = SkFontMgr::RefDefault();

		auto fDrawView = [&](const TChar view[], size_t count)
		{
			if (!count)
				return;

			SkRect measure;
			font.measureText(view, count * sizeof(TChar), encoding, &measure);
			canvas->drawSimpleText(view, count * sizeof(TChar), encoding, x, y, font, paint);
			height = std::max(height, measure.height());
			x += measure.width() + font.getSize() / 4.f;
		};

		size_t lastValid = 0;
		for (size_t i = 0; bFixTypeface && i < lenght; i++)
		{
			// if the typeface can't find the proper glyph, try to match a new one to render the str[i]
			if (font.getTypeface() && !font.getTypeface()->unicharToGlyph(str[i]))
			{
				// process first part of the line
				fDrawView(str + lastValid, i - lastValid);
				lastValid = i;

				// match a new SkTypeface, could return nullptr if no family can be found for the character
				if (sk_sp<SkTypeface> spNewTypeFace{ fontManager->matchFamilyStyleCharacter(nullptr, {}, nullptr, 0, str[i]) })
					font.setTypeface(spNewTypeFace);
			}
		}

		// process remaining chars in the string
		fDrawView(str + lastValid, lenght - lastValid);

		return height + font.getSize() / 4.f;
	}

	void DrawSkText(SkCanvas* canvas, const std::vector<std::wstring>& sText, const char familyName[], SkScalar x, SkScalar y, const SkPaint& paint, bool bFixTypeface)
	{
		sk_sp<SkFontMgr> fontManager = SkFontMgr::RefDefault();
		sk_sp<SkTypeface> typeface(fontManager->matchFamilyStyle(familyName, {}));
		SkFont font(typeface, 20);

		if (!familyName)
			familyName = sDefaultFamily;

		y += DrawAndMeatureString(canvas, familyName, strlen(familyName), font, paint, x, y, bFixTypeface);
		for (auto& str : sText)
			y += DrawAndMeatureString(canvas, str.c_str(), str.length(), font, paint, x, y, bFixTypeface);
	}
}

void ExampleLayer6::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	SkPaint paint;
	paint.setColor(SkColors::kWhite);
	DrawSkText(canvas, sText, nullptr, 100, 100, paint, false);

	paint.setColor(SkColors::kRed);
	DrawSkText(canvas, sText, "Yu Gothic UI", 400, 100, paint, false);

	paint.setColor(SkColors::kGreen);
	DrawSkText(canvas, sText, "Yu Gothic UI", 700, 100, paint, true);
}