#ifndef IBACKGROUND_H_4EDFBCC5_00F9_4767_AFFB_55E24608824D
#define IBACKGROUND_H_4EDFBCC5_00F9_4767_AFFB_55E24608824D

#include "include/core/SkSurface.h"
#include <string>

struct IBackground
{
	virtual std::wstring GetName() const = 0;
	virtual sk_sp<SkSurface> CreateSurface(int widht, int height) = 0;
	virtual void Destroy() = 0;
	virtual void SwapBuffers() = 0;
};

#endif // IBACKGROUND_H_4EDFBCC5_00F9_4767_AFFB_55E24608824D
