#include "include/Layers/ExampleLayer4.h"
#include "include/core/SkFont.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkTextBlob.h"

void ExampleLayer4::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

  SkFontStyle fontStyle;  // Default is normal weight, normal width,  upright slant.
  sk_sp<SkFontMgr> fontManager = SkFontMgr::RefDefault();
  sk_sp<SkTypeface> typeface(fontManager->matchFamilyStyle(nullptr, fontStyle));

  SkFont font1(typeface, 64.0f, 1.0f, 0.0f);
  SkFont font2(typeface, 64.0f, 1.5f, 0.0f);
  font1.setEdging(SkFont::Edging::kAntiAlias);
  font2.setEdging(SkFont::Edging::kAntiAlias);

  // Note: MakeFromString may fail to produce expected results if the typeface
  // does not have glyphs for the characters in the string.  The characters
  // will not be kerned or shaped beyond a simple mapping from one Unicode
  // code point to one glyph with a default advance.
  sk_sp<SkTextBlob> blob1 = SkTextBlob::MakeFromString("Skia", font1);
  sk_sp<SkTextBlob> blob2 = SkTextBlob::MakeFromString("Skia", font2);

  SkPaint paint1, paint2, paint3;

  paint1.setAntiAlias(true);
  paint1.setColor(SkColorSetARGB(0xFF, 0x42, 0x85, 0xF4));

  paint2.setAntiAlias(true);
  paint2.setColor(SkColorSetARGB(0xFF, 0xDB, 0x44, 0x37));
  paint2.setStyle(SkPaint::kStroke_Style);
  paint2.setStrokeWidth(3.0f);

  paint3.setAntiAlias(true);
  paint3.setColor(SkColorSetARGB(0xFF, 0x0F, 0x9D, 0x58));

  canvas->drawTextBlob(blob1.get(), 200.0f, 240.0f, paint1);
  canvas->drawTextBlob(blob1.get(), 200.0f, 344.0f, paint2);
  canvas->drawTextBlob(blob2.get(), 200.0f, 424.0f, paint3);

	__super::Draw(canvas);
	m_FPS.DrawFPS(canvas);
}