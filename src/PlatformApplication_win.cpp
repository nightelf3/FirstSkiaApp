#include "include/core/SkCanvas.h"
#include "include/Application.h"

#include <Windows.h>

//TODO: add base layer
class FirstLayer : public ILayer
{
	void Draw(SkCanvas* canvas) override
	{
		const auto bounds = canvas->getDeviceClipBounds();
		canvas->clear(SkColors::kBlack);

		SkPaint paint;
		paint.setStyle(SkPaint::Style::kFill_Style);
		paint.setColor(SkColors::kRed);

		SkRect rect = SkRect::MakeWH(bounds.width() / 2.f, bounds.height() / 2.f);
		rect.offsetTo(bounds.width() / 4.f, bounds.height() / 4.f);
		canvas->drawRect(rect, paint);
	}

	void Resize(int w, int h) override {}
	bool ProcessKey(Key key, InputState state, ModifierKey modifiers) override { return false; }
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override { return false; }
	bool ProcessMouseWheel(InputState state, ModifierKey modifiers) override { return false; }
	bool DrawOnIdle() const override { return false; }
};

class SecondLayer : public ILayer
{
	void Draw(SkCanvas* canvas) override
	{
		const auto bounds = canvas->getDeviceClipBounds();
		canvas->clear(SkColors::kWhite);

		SkPaint paint;
		paint.setStyle(SkPaint::Style::kFill_Style);
		paint.setColor(SkColors::kRed);

		SkRect rect = SkRect::MakeWH(bounds.width() / 2.f, bounds.height() / 2.f);
		rect.offsetTo(bounds.width() / 4.f, bounds.height() / 4.f);
		canvas->drawRect(rect, paint);
	}

	void Resize(int w, int h) override {}
	bool ProcessKey(Key key, InputState state, ModifierKey modifiers) override { return false; }
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override { return false; }
	bool ProcessMouseWheel(InputState state, ModifierKey modifiers) override { return false; }
	bool DrawOnIdle() const override { return false; }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application app;

	app.AddLayer(std::make_shared<FirstLayer>());
	app.AddLayer(std::make_shared<SecondLayer>());

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
					app.OnIdle();
				}
				idled = false;
			}
			DispatchMessage(&msg);
		}
		else
		{
			app.OnIdle();
			idled = true;
			Sleep(1);
		}
	}

	return (int)msg.wParam;
}
