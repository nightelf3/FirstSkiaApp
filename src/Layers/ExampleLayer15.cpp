#include "include/Layers/ExampleLayer15.h"
#include "include/Layers/Utils/Utils.h"
#include "include/core/SkColorFilter.h"

ExampleLayer15::ExampleLayer15()
{
  m_Image = LoadImageFromFile(SkString("resources/doge.png"));
}

void ExampleLayer15::Draw(SkCanvas* canvas)
{
	// clear canvas with black color
	canvas->clear(SkColors::kBlack);

  SkScalar colorMatrix1[20] = {
      0, 1, 0, 0, 0,
      0, 0, 1, 0, 0,
      1, 0, 0, 0, 0,
      0, 0, 0, 1, 0 };
  SkPaint paint;
  paint.setColorFilter(SkColorFilters::Matrix(colorMatrix1));
  canvas->drawImage(m_Image, 100, 100, {}, &paint);

  SkScalar grayscale[20] = {
      0.21f, 0.72f, 0.07f, 0.0f, 0.0f,
      0.21f, 0.72f, 0.07f, 0.0f, 0.0f,
      0.21f, 0.72f, 0.07f, 0.0f, 0.0f,
      0.0f,  0.0f,  0.0f,  1.0f, 0.0f };
  SkPaint paint2;
  paint2.setColorFilter(SkColorFilters::Matrix(grayscale));
  canvas->drawImage(m_Image, 1000, 100, {}, &paint2);
}