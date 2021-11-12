#include "include/Controls/BaseValueControl.h"
#include "include/Layers/Utils/Utils.h"

BaseValueControl::~BaseValueControl() = default;
BaseValueControl::BaseValueControl(SkScalar value, SkScalar min, SkScalar max) :
	m_Value(value), m_Min(min), m_Max(max)
{
}