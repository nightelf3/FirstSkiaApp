#pragma once

#include "include/core/SkSurface.h"
#include <string>

struct IBackground
{
	virtual ~IBackground() = default;
	virtual std::wstring GetName() const = 0;
	virtual sk_sp<SkSurface> CreateSurface(int widht, int height) = 0;
	virtual void Destroy() = 0;
	virtual void SwapBuffers() = 0;
};
