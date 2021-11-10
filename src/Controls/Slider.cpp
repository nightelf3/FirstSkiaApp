#include "include/Controls/Slider.h"
#include "include/Layers/Utils/Utils.h"

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

	SkRect GetTrackRect(const SkRect& bounds)
	{
		return SkRect::MakeXYWH(bounds.left() + kThumbWidth / 2.0f, bounds.centerY() - kTrackHeight / 2.0f, bounds.width() - kThumbWidth - kEditWidth - kEditPadding, kTrackHeight);
	}

	SkRect GetThumbRect(const SkRect& bounds, SkScalar value)
	{
		const SkRect track = GetTrackRect(bounds);
		return SkRect::MakeXYWH(track.left() + track.width() * value - kThumbWidth / 2.0f, track.centerY() - kThumbHeight / 2.0f, kThumbWidth, kThumbHeight);
	}

	SkRect GetEditRect(const SkRect& bounds)
	{
		const SkRect track = GetTrackRect(bounds);
		return SkRect::MakeXYWH(track.right() + kEditPadding, track.centerY() - kThumbHeight / 2.0f, kEditWidth, kThumbHeight);
	}

	SkScalar GetValueFromPos(const SkRect& bounds, SkScalar x)
	{
		const SkRect track = GetTrackRect(bounds);
		return GetClamped((x - track.left()) / track.width(), 0.0f, 1.0f);
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

Slider::Slider(SkString caption) :
	m_Caption(std::move(caption))
{
}

void Slider::Draw(SkCanvas* canvas, const SkRect& bounds)
{
	SkRect trackBounds = bounds;
	if (!m_Caption.isEmpty())
	{
		SkPaint paint;
		paint.setAntiAlias(true);
		paint.setColor(SkColors::kBlack);
		DrawSimpleText(canvas, m_Caption, GetTextPoint(m_Caption, bounds, kEditTextPadding, &paint), paint);
		trackBounds.fLeft += GetTextSize(m_Caption).width() + kEditPadding;
	}

	DrawRectAndOutline(canvas, GetTrackRect(trackBounds), SkColors::kGray, m_Active);
	DrawRectAndOutline(canvas, GetThumbRect(trackBounds, GetValue()), SkColors::kGray, m_Active);
	DrawEditBox(canvas, GetEditRect(trackBounds), GetValue(), m_Active);

	return __super::Draw(canvas, trackBounds);
}

bool Slider::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	m_Active = m_MouseDown || __super::ProcessMouse(x, y, state, modifiers);
	if (!m_Active)
		return false;

	switch (state)
	{
	case InputState::kDown:
		m_MouseDown = true;
		SetValue(GetValueFromPos(GetBounds(), x));
		break;

	case InputState::kUp:
		SetValue(GetValueFromPos(GetBounds(), x));
		m_MouseDown = false;
		break;

	case InputState::kMove:
		if (m_MouseDown)
			SetValue(GetValueFromPos(GetBounds(), x));
		break;
	}

	return true;
}

SkScalar Slider::GetHeight() const
{
	return kThumbHeight;
}
