#pragma once

#include "include/core/SkCanvas.h"
#include "include/core/SkString.h"
#include "include/core/SkFont.h"
#include "include/core/SkPaint.h"

#include <optional>

namespace DrawUtils
{
	struct DrawParameters
	{
		std::optional<SkColor> background = std::nullopt;
		std::optional<SkColor> outline = std::nullopt;
		SkScalar border = 1.0f;
	};

	const DrawParameters& GetDefaultParameters(bool active = false);
	void DrawRect(SkCanvas* canvas, const SkRect& bounds, const DrawUtils::DrawParameters& params = GetDefaultParameters());
	void DrawRoundRect(SkCanvas* canvas, const SkRect& bounds, SkScalar rx, SkScalar ry, const DrawUtils::DrawParameters& params = GetDefaultParameters());

	SkFont GetFont();
	void DrawSimpleText(SkCanvas* canvas, const SkString& str, const SkPoint& pt, const SkPaint& paint);
	SkSize GetTextSize(const SkString& str, std::optional<SkPaint> paint = std::nullopt);
	SkPoint GetTextPoint(const SkString& str, const SkRect& rect, SkScalar xOffset, std::optional<SkPaint> paint = std::nullopt);
}
