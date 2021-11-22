#pragma once

#include "include/Interfaces/IControlValue.h"
#include <algorithm>

struct ValueControlParams
{
	ValueControlParams(SkScalar value = 0.0f, SkScalar min = 0.0f, SkScalar max = 1.0f) :
		m_Value(value), m_Min(min), m_Max(max)
	{}

	SkScalar m_Value = 0.0f;
	SkScalar m_Min = 0.0f;
	SkScalar m_Max = 1.0f;
};

template<typename T>
class BaseValueControl : public IControlValue
{
public:
	BaseValueControl(const T& data) : m_Data(data) {}
	~BaseValueControl() override = default;

	SkScalar GetValue() const override { return m_Data.m_Value; }
	void SetValue(SkScalar value) override { m_Data.m_Value = std::clamp(value, GetMinValue(), GetMaxValue()); }

protected:
	T& GetParams() { return m_Data; }
	SkScalar GetMinValue() const { return m_Data.m_Min; }
	SkScalar GetMaxValue() const { return m_Data.m_Max; }

private:
	T m_Data;
};
