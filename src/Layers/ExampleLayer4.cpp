#include "include/Layers/ExampleLayer4.h"
#include "include/core/SkFont.h"
#include "include/core/SkFontMgr.h"

void ExampleLayer4::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	sk_sp<SkFontMgr> fontManager = SkFontMgr::RefDefault();
	sk_sp<SkTypeface> typeface(fontManager->matchFamilyStyle(nullptr, {}));

	SkFont font1(typeface, 64.0f, 1.0f, 0.0f);
	SkFont font2(typeface, 64.0f, 1.5f, 0.0f);
	font1.setEdging(SkFont::Edging::kAntiAlias);
	font2.setEdging(SkFont::Edging::kAntiAlias);

	SkPaint paint1;
	paint1.setAntiAlias(true);
	paint1.setColor(SkColorSetARGB(0xFF, 0x42, 0x85, 0xF4));
	canvas->drawString("Skia", 200.0f, 240.0f, font1, paint1);

	SkPaint paint2;
	paint2.setAntiAlias(true);
	paint2.setColor(SkColorSetARGB(0xFF, 0xDB, 0x44, 0x37));
	paint2.setStyle(SkPaint::kStroke_Style);
	paint2.setStrokeWidth(3.0f);
	canvas->drawString("Skia", 200.0f, 344.0f, font1, paint2);

	SkPaint paint3;
	paint3.setAntiAlias(true);
	paint3.setColor(SkColorSetARGB(0xFF, 0x0F, 0x9D, 0x58));
	canvas->drawString("Skia", 200.0f, 424.0f, font2, paint3);

	__super::Draw(canvas);

	m_FPS.Calc();
	m_FPS.Draw(canvas);
}