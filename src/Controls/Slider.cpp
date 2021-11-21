#include "include/Controls/Slider.h"
#include "include/Utils/Utils.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkFont.h"
#include "include/core/SkFontMgr.h"

namespace
{
	constexpr SkScalar kTrackHeight = 6.0f; // in px
	constexpr SkScalar kThumbWidth = 8.0f; // in px
	constexpr SkScalar kThumbHeight = 20.0f; // in px
	constexpr SkScalar kEditWidth = 30.0f; // in px
	constexpr SkScalar kEditPadding = kThumbWidth / 2.0f + 4.0f; // in px
	constexpr SkScalar kEditTextPadding = 2.0f; // in px
	constexpr size_t kMaxChars = 5;

	SkRect GetTrackRect(const SkRect& bounds)
	{
		return SkRect::MakeXYWH(bounds.left() + kThumbWidth / 2.0f, bounds.centerY() - kTrackHeight / 2.0f, bounds.width() - kThumbWidth - kEditWidth - kEditPadding, kTrackHeight);
	}

	SkRect GetThumbRect(const SkRect& bounds, SkScalar value, SkScalar min, SkScalar max)
	{
		value = (value - min) / (max - min);
		const SkRect track = GetTrackRect(bounds);
		return SkRect::MakeXYWH(track.left() + track.width() * value - kThumbWidth / 2.0f, track.centerY() - kThumbHeight / 2.0f, kThumbWidth, kThumbHeight);
	}

	SkRect GetEditRect(const SkRect& bounds)
	{
		const SkRect track = GetTrackRect(bounds);
		return SkRect::MakeXYWH(track.right() + kEditPadding, track.centerY() - kThumbHeight / 2.0f, kEditWidth, kThumbHeight);
	}

	SkScalar GetValueFromPos(const SkRect& bounds, SkScalar x, SkScalar min, SkScalar max)
	{
		const SkRect track = GetTrackRect(bounds);
		return std::clamp((x - track.left()) / track.width(), 0.0f, 1.0f) * (max - min) + min ;
	}

	void DrawRectAndOutline(SkCanvas* canvas, const SkRect& bounds, const SkColor4f& bgColor, bool bActive)
	{
		SkPaint paint;
		paint.setColor(bgColor);
		paint.setStyle(SkPaint::kFill_Style);
		canvas->drawRect(bounds, paint);

		paint.setColor(bActive ? SkColors::kBlue : SkColors::kLtGray);
		paint.setStyle(SkPaint::kStroke_Style);
		canvas->drawRect(bounds, paint);
	}

	SkFont GetFont()
	{
		sk_sp<SkFontMgr> fontManager = SkFontMgr::RefDefault();
		sk_sp<SkTypeface> typeface(fontManager->matchFamilyStyle(nullptr, {}));
		return SkFont{typeface, 11};
	}

	void DrawSimpleText(SkCanvas* canvas, const SkString& str, const SkPoint& pt, const SkPaint& paint)
	{
		const SkFont font = GetFont();
		canvas->drawSimpleText(str.c_str(), str.size(), SkTextEncoding::kUTF8, pt.x(), pt.y(), font, paint);
	}

	SkSize GetTextSize(const SkString& str, SkPaint* paint = nullptr)
	{
		const SkFont font = GetFont();
		SkRect measure;
		font.measureText(str.c_str(), str.size(), SkTextEncoding::kUTF8, &measure, paint);
		return SkSize::Make(measure.width(), measure.height());
	}

	SkPoint GetTextPoint(const SkString& str, const SkRect& rect, SkScalar xOffset, SkPaint* paint = nullptr)
	{
		const SkSize textSize = GetTextSize(str, paint);
		return SkPoint::Make(rect.x() + xOffset, rect.bottom() - (rect.height() - textSize.height()) / 2.0f);
	}

	SkString ToString(SkScalar value)
	{
		SkString str;
		str.printf("%.3f", value);
		if (str.size() > kMaxChars)
		{
			str.resize(kMaxChars);
			if (str[kMaxChars - 1] == '.')
				str.resize(kMaxChars - 1);
		}
		return str;
	}

	void DrawEditBox(SkCanvas* canvas, const SkRect& bounds, SkScalar value, bool bActive)
	{
		DrawRectAndOutline(canvas, bounds, SkColors::kWhite, bActive);

		SkPaint paint;
		paint.setAntiAlias(true);
		paint.setColor(SkColors::kBlack);
		const SkString str = ToString(value);
		DrawSimpleText(canvas, str, GetTextPoint(str, bounds, kEditTextPadding, &paint), paint);
	}
}

Slider::Slider(SkScalar value, SkScalar min, SkScalar max, SkString caption) :
	BaseControl(std::move(caption)),
	BaseValueControl(value, min, max)
{
}

void Slider::Draw(SkCanvas* canvas, const SkRect& bounds)
{
	SkRect trackBounds = bounds;
	if (!GetCaption().isEmpty())
	{
		SkPaint paint;
		paint.setAntiAlias(true);
		paint.setColor(SkColors::kBlack);
		DrawSimpleText(canvas, GetCaption(), GetTextPoint(GetCaption(), bounds, kEditTextPadding, &paint), paint);
		trackBounds.fLeft += GetTextSize(GetCaption()).width() + kEditPadding;
	}

	DrawRectAndOutline(canvas, GetTrackRect(trackBounds), SkColors::kGray, IsActive());
	DrawRectAndOutline(canvas, GetThumbRect(trackBounds, GetValue(), GetMinValue(), GetMaxValue()), SkColors::kGray, IsActive());
	DrawEditBox(canvas, GetEditRect(trackBounds), GetValue(), IsActive());

	return __super::Draw(canvas, trackBounds);
}

SkScalar Slider::GetHeight() const
{
	return kThumbHeight;
}

void Slider::OnMouseDown(int x, int y, ModifierKey modifiers)
{
	SetValue(GetValueFromPos(GetBounds(), x, GetMinValue(), GetMaxValue()));
}

void Slider::OnMouseMove(int x, int y, ModifierKey modifiers, bool active)
{
	if (active)
		SetValue(GetValueFromPos(GetBounds(), x, GetMinValue(), GetMaxValue()));
}

void Slider::OnMouseUp(int x, int y, ModifierKey modifiers)
{
	SetValue(GetValueFromPos(GetBounds(), x, GetMinValue(), GetMaxValue()));
}
