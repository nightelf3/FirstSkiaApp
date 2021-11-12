#pragma once

#include "include/core/SkScalar.h"

struct IControlValue
{
	virtual ~IControlValue() = default;
	virtual SkScalar GetValue() const = 0;
	virtual void SetValue(SkScalar value) = 0;
};
