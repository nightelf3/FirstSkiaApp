#ifndef IPLATFORMWINDOW_H_C00D52D7_AB05_4F18_9DB7_08A25594EF42
#define IPLATFORMWINDOW_H_C00D52D7_AB05_4F18_9DB7_08A25594EF42

#include "IApplication.h"
#include "include/core/SkSurface.h"
#include <memory>

struct IPlatformWindow
{
	virtual void Show() = 0;
	virtual void Draw() = 0;
	virtual sk_sp<SkSurface> Resize(int width, int height) = 0;
	virtual void Invalidate() = 0;
	virtual void SetTitle(const std::wstring& title) = 0;
};

std::unique_ptr<IPlatformWindow> CreatePlatformWindow(IApplication* application);

#endif // IPLATFORMWINDOW_H_C00D52D7_AB05_4F18_9DB7_08A25594EF42