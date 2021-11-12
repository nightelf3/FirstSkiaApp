#pragma once

#include "include/Interfaces/IControlValue.h"
#include <algorithm>

class BaseValueControl : public IControlValue
{
public:
	BaseValueControl(SkScalar value = 0.0f, SkScalar min = 0.0f, SkScalar max = 1.0f);
	~BaseValueControl() override;

	SkScalar GetValue() const override { return m_Value; }
	void SetValue(SkScalar value) override { m_Value = std::clamp(value, m_Min, m_Max); }

protected:
	SkScalar GetMinValue() const { return m_Min; }
	SkScalar GetMaxValue() const { return m_Max; }

private:
	SkScalar m_Value = 0.0f;
	const SkScalar m_Min = 0.0f;
	const SkScalar m_Max = 1.0f;
};
