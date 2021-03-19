#include "include/core/SkCanvas.h"
#include "include/AppWindow.h"

class FirstLayer : public ILayer
{
	void Draw(SkSurface* surface) override
	{
		surface->getCanvas()->clear(SkColors::kBlack);

		SkPaint paint;
		paint.setStyle(SkPaint::Style::kFill_Style);
		paint.setColor(SkColors::kRed);

		SkRect rect = SkRect::MakeWH(surface->width() / 2.f, surface->height() / 2.f);
		rect.offsetTo(surface->width() / 4.f, surface->height() / 4.f);
		surface->getCanvas()->drawRect(rect, paint);
	}

	void Resize(int w, int h) override {}
	bool ProcessKey(Key key, InputState state, ModifierKey modifiers) override { return false; }
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override { return false; }
	bool ProcessMouseWheel(InputState state, ModifierKey modifiers) override { return false; }
	bool DrawOnIdle() const override { return true; }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	AppWindow wnd(std::make_unique<FirstLayer>());

	MSG msg;
	memset(&msg, 0, sizeof(msg));

	// Main message loop
	bool idled = false;
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			if (WM_PAINT == msg.message)
			{
				// Ensure that call onIdle at least once per WM_PAINT, or mouse events can
				// overwhelm the message processing loop, and prevent animation from running.
				if (!idled) {
					wnd.OnIdle();
				}
				idled = false;
			}
			DispatchMessage(&msg);
		}
		else
		{
			wnd.OnIdle();
			idled = true;
		}
	}

	return (int)msg.wParam;
}
