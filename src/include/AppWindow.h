#ifndef WINDOW_H_79E41F56_5C03_42AE_A084_9058DBDEEE82
#define WINDOW_H_79E41F56_5C03_42AE_A084_9058DBDEEE82

#include "ILayer.h"

#include <vector>
#include <Windows.h>

class AppWindow
{
public:
	AppWindow(std::unique_ptr<ILayer> layer = nullptr);
	~AppWindow();

	void OnPaint();
	void OnIdle();
	void OnResize(int w, int h);
	bool OnKey(Key key, InputState state, ModifierKey modifiers);
	bool OnMouse(int x, int y, InputState state, ModifierKey modifiers);
	bool OnMouseWheel(InputState state, ModifierKey modifiers);

	void Invalidate();
	void SwapBuffers();

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	std::unique_ptr<ILayer> m_Layer;
	int m_Width = 640;
	int m_Height = 480;

	sk_sp<SkSurface> m_Surface;
	std::vector<uint8_t> m_SurfaceMemory;
};

#endif // WINDOW_H_79E41F56_5C03_42AE_A084_9058DBDEEE82
