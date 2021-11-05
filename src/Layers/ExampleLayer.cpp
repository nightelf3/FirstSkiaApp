#include "include/Layers/ExampleLayer.h"
#include "include/Layers/Utils/Utils.h"
#include "include/Controls/Slider.h"

namespace
{
	constexpr SkScalar kPanelSize = 300.0f;  // in px
	constexpr SkScalar kPanelRadius = 10.0f;  // in px

	SkRect GetDataRect(SkRect bounds)
	{
		bounds.fRight -= kPanelSize;
		return bounds;
	}

	SkRect GetPanelRect(SkRect bounds)
	{
		bounds.fLeft = bounds.fRight - kPanelSize;
		return bounds.makeInset(kPanelRadius, kPanelRadius);
	}

	Slider slider;
}

ExampleLayer::ExampleLayer()
{
	m_Image = LoadImageFromFile(SkString("resources/8k.jpg"));
}

void ExampleLayer::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

	const SkRect bounds = GetBounds(canvas);
	{  // draw the image
		SkAutoCanvasRestore guard(canvas, true);
		const SkRect imageRect = SkRect::MakeWH(m_Image->width(), m_Image->height());
		const SkRect dataRect = GetDataRect(bounds);
		SkMatrix matrix = SkMatrix::RectToRect(imageRect, dataRect, SkMatrix::kCenter_ScaleToFit);
		matrix.postRotate(slider.GetValue() * 360.0f, dataRect.centerX(), dataRect.centerY());
		canvas->setMatrix(matrix);
		canvas->drawImage(m_Image, 0.0f, 0.0f);
	}

	{  // draw the panel
		SkPaint paint;
		paint.setColor(SkColors::kDkGray);
		paint.setStyle(SkPaint::kFill_Style);
		const SkRect panelRect = GetPanelRect(bounds);
		canvas->drawRoundRect(panelRect, kPanelRadius, kPanelRadius, paint);

		paint.setColor(SkColors::kGray);
		paint.setStyle(SkPaint::kStroke_Style);
		canvas->drawRoundRect(panelRect, kPanelRadius, kPanelRadius, paint);

		slider.Draw(canvas, SkRect::MakeXYWH(panelRect.left(), panelRect.top(), panelRect.width(), 20.0f));
	}
}

bool ExampleLayer::ProcessMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	return slider.ProcessMouse(x, y, state, modifiers);
}