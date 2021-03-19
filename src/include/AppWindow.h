#ifndef WINDOW_H_79E41F56_5C03_42AE_A084_9058DBDEEE82
#define WINDOW_H_79E41F56_5C03_42AE_A084_9058DBDEEE82

#include "LayerCollection.h"
#include <vector>
#include <Windows.h>

class AppWindow
{
public:
	AppWindow();
	~AppWindow();

	void AddLayer(spLayer&& layer);
	void OnPaint();
	void OnIdle();
	void OnResize(int w, int h);
	bool OnKey(Key key, InputState state, ModifierKey modifiers);
	bool OnMouse(int x, int y, InputState state, ModifierKey modifiers);
	bool OnMouseWheel(InputState state, ModifierKey modifiers);

	void Invalidate();
	void SwapBuffers();

private:
	//TODO: move to platform window
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_Width = CW_USEDEFAULT;
	int m_Height = CW_USEDEFAULT;

	LayerCollection m_Layers;

	sk_sp<SkSurface> m_Surface;
	std::vector<uint8_t> m_SurfaceMemory;
};

#endif // WINDOW_H_79E41F56_5C03_42AE_A084_9058DBDEEE82
