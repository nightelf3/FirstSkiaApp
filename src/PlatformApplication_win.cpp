#include "include/core/SkCanvas.h"
#include "include/Application.h"

#include "include/Layers/ExampleLayer1.h"
#include "include/Layers/ExampleLayer2.h"
#include "include/Layers/ExampleLayer3.h"
#include "include/Layers/ExampleLayer4.h"
#include "include/Layers/ExampleLayer5.h"
#include "include/Layers/ExampleLayer6.h"
#include "include/Layers/ExampleLayer7.h"
#include "include/Layers/ExampleLayer8.h"
#include "include/Layers/ExampleLayer9.h"
#include "include/Layers/ExampleLayer10.h"
#include "include/Layers/ExampleLayer11.h"
#include "include/Layers/ExampleLayer12.h"
#include "include/Layers/ExampleLayer13.h"
#include "include/Layers/ExampleLayer14.h"
#include "include/Layers/ExampleLayer15.h"
#include "include/Layers/ThankYouLayer.h"

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application app;
	app.AddLayer(std::make_shared<ExampleLayer1>());
	app.AddLayer(std::make_shared<ExampleLayer2>());
	app.AddLayer(std::make_shared<ExampleLayer3>());
	app.AddLayer(std::make_shared<ExampleLayer4>());
	app.AddLayer(std::make_shared<ExampleLayer5>());
	app.AddLayer(std::make_shared<ExampleLayer6>());
	app.AddLayer(std::make_shared<ExampleLayer7>());
	app.AddLayer(std::make_shared<ExampleLayer8>());
	app.AddLayer(std::make_shared<ExampleLayer9>());
	app.AddLayer(std::make_shared<ExampleLayer10>());
	app.AddLayer(std::make_shared<ExampleLayer11>());
	app.AddLayer(std::make_shared<ExampleLayer12>());
	app.AddLayer(std::make_shared<ExampleLayer13>());
	app.AddLayer(std::make_shared<ExampleLayer14>());
	app.AddLayer(std::make_shared<ExampleLayer15>());
	app.AddLayer(std::make_shared<ThankYouLayer>());
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
