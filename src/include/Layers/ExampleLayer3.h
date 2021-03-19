#ifndef EXAMPLELAYER3_H_F0693353_488C_432D_A3D9_D0B3E3BFCD9B
#define EXAMPLELAYER3_H_F0693353_488C_432D_A3D9_D0B3E3BFCD9B

#include "BaseLayer.h"
#include <list>
#include "include/core/SkPath.h"

struct IRandomShape
{
	virtual void Draw(SkCanvas* canvas) = 0;
};

struct BaseRandomShape : public IRandomShape
{
	BaseRandomShape();
	SkScalar RandomScalar(SkScalar from, SkScalar to) const;
	SkColor RandomColor() const;
	SkPaint::Style RandomStyle() const;

protected:
	SkPaint m_Paint;
};

class RandomRect : public BaseRandomShape
{
public:
	RandomRect(int x, int y);
	void Draw(SkCanvas* canvas) override;

protected:
	SkRect m_Rect;
};

class RandomRRect : public RandomRect
{
public:
	RandomRRect(int x, int y);
	void Draw(SkCanvas* canvas) override;

private:
	SkScalar m_Radius;
};

class RandomCircle : public BaseRandomShape
{
public:
	RandomCircle(int x, int y);
	void Draw(SkCanvas* canvas) override;

private:
	SkPoint m_Center;
	SkScalar m_Radius;
};

class RandomPath : public BaseRandomShape
{
public:
	RandomPath(int x, int y);
	void Draw(SkCanvas* canvas) override;

private:
	SkPath m_Path;
};

class ExampleLayer3 final : public BaseLayer
{
public:
	ExampleLayer3();

	std::wstring GetTitle() const override { return L"Example #3: Draw random shapes on click"; };
	void Draw(SkCanvas* canvas) override;
	bool ProcessKey(Key key, InputState state, ModifierKey modifiers) override;
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override;

private:
	std::list<std::unique_ptr<IRandomShape>> m_Shapes;
};

#endif // EXAMPLELAYER3_H_F0693353_488C_432D_A3D9_D0B3E3BFCD9B
