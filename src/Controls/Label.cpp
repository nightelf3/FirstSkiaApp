#include "include/Controls/Label.h"
#include "include/Utils/DrawUtils.h"

#include "include/core/SkCanvas.h"

Label::Label(SkString caption) :
	BaseControl(std::move(caption))
{
}

Label::Label(const LabelParams& params, SkString caption) :
	BaseControl(std::move(caption)),
	m_Params(params)
{
}

void Label::Draw(SkCanvas* canvas, const SkRect& bounds)
{
	const SkString& caption = GetCaption();
	if (caption.isEmpty())
		return;

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setColor(SkColors::kWhite);

	const SkPoint pt = GetTextPoint(bounds, paint);
	canvas->drawSimpleText(caption.c_str(), caption.size(), SkTextEncoding::kUTF8, pt.x(), pt.y(), m_Params.font, paint);
}

SkScalar Label::GetHeight() const
{
	if (GetCaption().isEmpty())
		return 0.0f;
	return DrawUtils::GetTextSize(GetCaption()).height();
}

SkPoint Label::GetTextPoint(const SkRect& bounds, const SkPaint& paint) const
{
	const SkSize textSize = DrawUtils::GetTextSize(GetCaption(), paint);
	const SkScalar fY = bounds.bottom() - (bounds.height() - textSize.height()) / 2.0f;

	switch (m_Params.align)
	{
	case Align::Center:
		return SkPoint::Make(bounds.left() + (bounds.width() - textSize.width()) / 2.0f, fY);

	case Align::Right:
		return SkPoint::Make(bounds.right() - textSize.width(), fY);
	}

	return SkPoint::Make(bounds.left(), fY);
}
