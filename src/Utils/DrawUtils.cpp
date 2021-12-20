#include "include/Utils/DrawUtils.h"
#include "include/core/SkFontMgr.h"

namespace
{
	SkRect GetOutlineRect(const SkRect& bounds, SkScalar border)
	{
		const SkScalar kHalfBorker = border * 0.5f;
		return bounds.makeInset(kHalfBorker, kHalfBorker);
	}
}

const DrawUtils::DrawParameters& DrawUtils::GetDefaultParameters(bool active)
{
	static std::vector<DrawParameters> defaults;
	if (defaults.empty())
	{
		defaults.resize(2);

		defaults[0].background = SkColors::kGray.toSkColor();
		defaults[0].outline = SkColors::kLtGray.toSkColor();

		defaults[1].background = SkColors::kGray.toSkColor();
		defaults[1].outline = SkColors::kWhite.toSkColor();
	}

	return defaults[active];
}

void DrawUtils::DrawRect(SkCanvas* canvas, const SkRect& bounds, const DrawUtils::DrawParameters& params)
{
	SkPaint paint;
	if (params.background)
	{
		paint.setColor(*params.background);
		paint.setStyle(SkPaint::kFill_Style);
		canvas->drawRect(bounds, paint);
	}

	if (params.outline)
	{
		paint.setColor(*params.outline);
		paint.setStyle(SkPaint::kStroke_Style);
		paint.setStrokeWidth(params.border);
		canvas->drawRect(GetOutlineRect(bounds, params.border), paint);
	}
}

void DrawUtils::DrawRoundRect(SkCanvas* canvas, const SkRect& bounds, SkScalar rx, SkScalar ry, const DrawUtils::DrawParameters& params)
{
	SkPaint paint;
	paint.setAntiAlias(true);

	if (params.background)
	{
		paint.setColor(*params.background);
		paint.setStyle(SkPaint::kFill_Style);
		canvas->drawRoundRect(bounds, rx, ry, paint);
	}

	if (params.outline)
	{
		paint.setColor(*params.outline);
		paint.setStyle(SkPaint::kStroke_Style);
		paint.setStrokeWidth(params.border);
		canvas->drawRoundRect(GetOutlineRect(bounds, params.border), rx, ry, paint);
	}
}

SkFont DrawUtils::GetFont()
{
	sk_sp<SkFontMgr> fontManager = SkFontMgr::RefDefault();
	sk_sp<SkTypeface> typeface(fontManager->matchFamilyStyle(nullptr, {}));
	return SkFont{typeface, 11};
}

void DrawUtils::DrawSimpleText(SkCanvas* canvas, const SkString& str, const SkPoint& pt, const SkPaint& paint)
{
	const SkFont font = GetFont();
	canvas->drawSimpleText(str.c_str(), str.size(), SkTextEncoding::kUTF8, pt.x(), pt.y(), font, paint);
}

SkSize DrawUtils::GetTextSize(const SkString& str, std::optional<SkPaint> paint)
{
	const SkFont font = GetFont();
	SkRect measure;
	font.measureText(str.c_str(), str.size(), SkTextEncoding::kUTF8, &measure, paint ? &(*paint) : nullptr);
	return SkSize::Make(measure.width(), measure.height());
}

SkPoint DrawUtils::GetTextPoint(const SkString& str, const SkRect& rect, SkScalar xOffset, std::optional<SkPaint> paint)
{
	const SkSize textSize = GetTextSize(str, paint);
	return SkPoint::Make(rect.x() + xOffset, rect.bottom() - (rect.height() - textSize.height()) / 2.0f);
}
