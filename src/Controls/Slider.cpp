#include "include/Controls/Slider.h"
#include "include/Utils/Utils.h"
#include "include/Utils/DrawUtils.h"

#include "include/core/SkCanvas.h"

namespace
{
	constexpr SkScalar kTrackHeight = 6.0f; // in px
	constexpr SkScalar kThumbWidth = 8.0f; // in px
	constexpr SkScalar kThumbHeight = 20.0f; // in px
	constexpr SkScalar kEditWidth = 30.0f; // in px
	constexpr SkScalar kPadding = 4.0f; // in px
	constexpr SkScalar kEditPadding = kThumbWidth / 2.0f + kPadding; // in px
	constexpr SkScalar kEditTextPadding = 4.0f; // in px
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
		return SkRect::MakeXYWH(track.right() + kEditPadding, track.centerY() - kThumbHeight / 2.0f, kEditWidth + kPadding, kThumbHeight);
	}

	SkScalar GetValueFromPos(const SkRect& bounds, SkScalar x, SkScalar min, SkScalar max)
	{
		return std::clamp((x - bounds.left()) / bounds.width(), 0.0f, 1.0f) * (max - min) + min ;
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
		auto paintParams = DrawUtils::GetDefaultParameters(bActive);
		paintParams.background = SkColors::kWhite.toSkColor();
		DrawUtils::DrawRect(canvas, bounds, paintParams);

		SkPaint paint;
		paint.setAntiAlias(true);
		paint.setColor(SkColors::kBlack);
		const SkString str = ToString(value);
		DrawUtils::DrawSimpleText(canvas, str, DrawUtils::GetTextPoint(str, bounds, kEditTextPadding, paint), paint);
	}
}

Slider::Slider(const SliderParams& params, SkString caption) :
	BaseControl(std::move(caption)),
	BaseValueControl(params)
{
}

void Slider::Draw(SkCanvas* canvas, const SkRect& bounds)
{
	SkRect trackBounds = bounds;
	if (!GetCaption().isEmpty())
	{
		SkPaint paint;
		paint.setAntiAlias(true);
		paint.setColor(SkColors::kWhite);
		DrawUtils::DrawSimpleText(canvas, GetCaption(), DrawUtils::GetTextPoint(GetCaption(), bounds, 0.0f, paint), paint);
		trackBounds.fLeft += DrawUtils::GetTextSize(GetCaption()).width() + kEditPadding - kPadding;
	}

	m_Track = GetTrackRect(trackBounds);
	DrawUtils::DrawRect(canvas, m_Track, DrawUtils::GetDefaultParameters(IsActive()));
	DrawUtils::DrawRect(canvas, GetThumbRect(trackBounds, GetValue(), GetMinValue(), GetMaxValue()), DrawUtils::GetDefaultParameters(IsActive()));
	DrawEditBox(canvas, GetEditRect(trackBounds), GetValue(), IsActive());

	return __super::Draw(canvas, bounds);
}

SkScalar Slider::GetHeight() const
{
	return kThumbHeight;
}

bool Slider::OnKey(Key key, InputState state, ModifierKey modifiers)
{
	if (InputState::kDown != state)
		return false;

	SkScalar increment = GetParams().m_Increment;
	if (modifiers.Has(ModifierKey::kShift))
		increment *= 10.0f;
	else if (modifiers.Has(ModifierKey::kControl))
		increment *= 0.1f;
	else if (modifiers.Has(ModifierKey::kAlt))
		increment *= 0.01f;

	switch (key)
	{
	case Key::kRight:
	case Key::kUp:
		SetValue(GetValue() + increment);
		break;
	case Key::kLeft:
	case Key::kDown:
		SetValue(GetValue() - increment);
		break;
	}

	return true;
}

bool Slider::OnMouseDown(int x, int y, ModifierKey modifiers)
{
	if (!Utils::IsXInRect(x, m_Track))
		return false;
	SetValue(GetValueFromPos(m_Track, x, GetMinValue(), GetMaxValue()));
	return true;
}

void Slider::OnMouseMove(int x, int y, ModifierKey modifiers, bool active)
{
	if (active)
		SetValue(GetValueFromPos(m_Track, x, GetMinValue(), GetMaxValue()));
}

void Slider::OnMouseUp(int x, int y, ModifierKey modifiers)
{
	SetValue(GetValueFromPos(m_Track, x, GetMinValue(), GetMaxValue()));
}
