#include "include/core/SkCanvas.h"
#include "include/Application.h"

#include "include/Layers/SwirlLayer.h"
#include "include/Layers/BlackAndWhiteLayer.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application app;
	app.AddLayer(std::make_shared<SwirlLayer>());
	app.AddLayer(std::make_shared<BlackAndWhiteLayer>());
	app.Show();

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
