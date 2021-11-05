#pragma once

#include "IApplication.h"
#include "IBackground.h"
#include "include/core/SkSurface.h"
#include <memory>

struct IPlatformWindow
{
	virtual ~IPlatformWindow() = default;
	virtual void Show() = 0;
	virtual void Draw() = 0;
	virtual sk_sp<SkSurface> Resize(int width, int height) = 0;
	virtual void Invalidate() = 0;
	virtual void SetTitle(const std::wstring& title) = 0;
	virtual const IBackground* GetBackgound() const = 0;
	virtual sk_sp<SkSurface> SetBackgound(std::unique_ptr<IBackground>&& background) = 0;
	virtual WHandle GetHandle() const = 0;
};

std::unique_ptr<IPlatformWindow> CreatePlatformWindow(IApplication* application);
