#pragma once

#include "BaseControl.h"
#include "include/Utils/DrawUtils.h"

enum class Align
{
	Left,
	Center,
	Right
};

struct LabelParams
{
	Align align = Align::Center;
	SkFont font = DrawUtils::GetFont();
};

class Label : public BaseControl
{
public:
	Label(SkString caption = {});
	Label(const LabelParams& params, SkString caption);
	~Label() override = default;

	void Draw(SkCanvas* canvas, const SkRect& bounds) override;
	SkScalar GetHeight() const override;

private:
	bool IsSupportInputState(skui::InputState state) const override { return false; }
	SkPoint GetTextPoint(const SkRect& bounds, const SkPaint& paint) const;

	LabelParams m_Params;
};
