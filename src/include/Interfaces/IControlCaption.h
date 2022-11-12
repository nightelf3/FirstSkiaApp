#pragma once

#include "include/core/SkString.h"

struct IControlCaption
{
	virtual ~IControlCaption() = default;
	virtual const SkString& GetCaption() const = 0;
	virtual void SetCaption(SkString caption) = 0;
};
