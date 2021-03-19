#include "include/Interfaces/IPlatformWindow.h"
#include "include/Types.h"

#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <vector>
#include <map>

namespace
{
	constexpr TCHAR g_sWindowClass[] = _T("FirstSkiaApp");

	ModifierKey get_modifiers(UINT message, WPARAM wParam, LPARAM lParam)
	{
		ModifierKey modifiers = ModifierKey::kNone;

		switch (message)
		{
		case WM_UNICHAR:
		case WM_CHAR:
			if (0 == (lParam & (1 << 30))) {
				modifiers |= ModifierKey::kFirstPress;
			}
			if (lParam & (1 << 29)) {
				modifiers |= ModifierKey::kOption;
			}
			break;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			if (0 == (lParam & (1 << 30))) {
				modifiers |= ModifierKey::kFirstPress;
			}
			if (lParam & (1 << 29)) {
				modifiers |= ModifierKey::kOption;
			}
			break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
			if (lParam & (1 << 29)) {
				modifiers |= ModifierKey::kOption;
			}
			break;

		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MOUSEMOVE:
		case WM_MOUSEWHEEL:
			if (wParam & MK_CONTROL) {
				modifiers |= ModifierKey::kControl;
			}
			if (wParam & MK_SHIFT) {
				modifiers |= ModifierKey::kShift;
			}
			break;
		}

		return modifiers;
	}

	Key get_key(WPARAM vk)
	{
		static const std::map<WPARAM, Key> gPair{
			{VK_BACK, Key::kBack},
			{VK_CLEAR, Key::kBack},
			{VK_RETURN, Key::kOK},
			{VK_UP, Key::kUp},
			{VK_DOWN, Key::kDown},
			{VK_LEFT, Key::kLeft},
			{VK_RIGHT, Key::kRight},
			{VK_TAB, Key::kTab},
			{VK_PRIOR, Key::kPageUp},
			{VK_NEXT, Key::kPageDown},
			{VK_HOME, Key::kHome},
			{VK_END, Key::kEnd},
			{VK_DELETE, Key::kDelete},
			{VK_ESCAPE, Key::kEscape},
			{VK_SHIFT, Key::kShift},
			{VK_CONTROL, Key::kCtrl},
			{VK_MENU, Key::kOption},
			{'A', Key::kA},
			{'C', Key::kC},
			{'V', Key::kV},
			{'X', Key::kX},
			{'Y', Key::kY},
			{'Z', Key::kZ}
		};

		auto it = gPair.find(vk);
		return it != gPair.end() ? it->second : Key::kUnknown;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	IApplication* window = reinterpret_cast<IApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (!window)
		return DefWindowProc(hWnd, message, wParam, lParam);

	bool eventHandled = false;
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		window->OnPaint();
		EndPaint(hWnd, &ps);
		eventHandled = true;
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		eventHandled = true;
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		eventHandled = true;
		break;

	case WM_SIZE:
		window->OnResize(LOWORD(lParam), HIWORD(lParam));
		eventHandled = true;
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		eventHandled = window->OnKey(get_key(wParam), InputState::kDown, get_modifiers(message, wParam, lParam));
		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		eventHandled = window->OnKey(get_key(wParam), InputState::kUp, get_modifiers(message, wParam, lParam));
		break;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP: {
		const int xPos = GET_X_LPARAM(lParam);
		const int yPos = GET_Y_LPARAM(lParam);
		const InputState iState = ((wParam & MK_LBUTTON) != 0) ? InputState::kDown : InputState::kUp;
		eventHandled = window->OnMouse(xPos, yPos, iState, get_modifiers(message, wParam, lParam));
		break;
	}

	case WM_MOUSEMOVE: {
		const int xPos = GET_X_LPARAM(lParam);
		const int yPos = GET_Y_LPARAM(lParam);
		eventHandled = window->OnMouse(xPos, yPos, InputState::kMove, get_modifiers(message, wParam, lParam));
		break;
	}

	case WM_MOUSEWHEEL:
		eventHandled = window->OnMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? InputState::kZoomIn : InputState::kZoomOut, get_modifiers(message, wParam, lParam));
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return eventHandled ? 0 : 1;
}

class PlatformWindow_Win : public IPlatformWindow
{
public:
	PlatformWindow_Win(IApplication* application) :
		m_hInstance(GetModuleHandle(nullptr))
	{
		static WNDCLASSEX wcex;
		static bool wcexInit = false;
		if (!wcexInit)
		{
			wcex.cbSize = sizeof(WNDCLASSEX);

			wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wcex.lpfnWndProc = WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = m_hInstance;
			wcex.hIcon = LoadIcon(m_hInstance, (LPCTSTR)IDI_WINLOGO);
			wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
			wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName = nullptr;
			wcex.lpszClassName = g_sWindowClass;
			wcex.hIconSm = LoadIcon(m_hInstance, (LPCTSTR)IDI_WINLOGO);

			if (RegisterClassEx(&wcex))
				wcexInit = true;
		}

		m_hWnd = CreateWindow(g_sWindowClass, nullptr, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			m_Width, m_Height, nullptr, nullptr, m_hInstance, nullptr);
		SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)application);
	}

	~PlatformWindow_Win()
	{
		DestroyWindow(m_hWnd);
	}

	void Show() override
	{
		ShowWindow(m_hWnd, SW_SHOW);
	}

	void Draw() override
	{
		BITMAPINFO* bmpInfo = reinterpret_cast<BITMAPINFO*>(m_SurfaceMemory.data());
		HDC dc = GetDC(m_hWnd);
		StretchDIBits(dc, 0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, bmpInfo->bmiColors,
			bmpInfo, DIB_RGB_COLORS, SRCCOPY);
		ReleaseDC(m_hWnd, dc);
	}

	sk_sp<SkSurface> Resize(int width, int height) override
	{
		m_Width = width;
		m_Height = height;

		const size_t bmpSize = sizeof(BITMAPINFOHEADER) + m_Width * m_Height * sizeof(uint32_t);
		m_SurfaceMemory.resize(bmpSize);

		BITMAPINFO* bmpInfo = reinterpret_cast<BITMAPINFO*>(m_SurfaceMemory.data());
		ZeroMemory(bmpInfo, sizeof(BITMAPINFO));
		bmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmpInfo->bmiHeader.biWidth = m_Width;
		bmpInfo->bmiHeader.biHeight = -m_Height; // negative means top-down bitmap. Skia draws top-down.
		bmpInfo->bmiHeader.biPlanes = 1;
		bmpInfo->bmiHeader.biBitCount = 32;
		bmpInfo->bmiHeader.biCompression = BI_RGB;
		void* pixels = bmpInfo->bmiColors;

		SkImageInfo info = SkImageInfo::Make(m_Width, m_Height, SkColorType::kBGRA_8888_SkColorType, kPremul_SkAlphaType, nullptr);
		return SkSurface::MakeRasterDirect(info, pixels, sizeof(uint32_t) * m_Width);
	}

	void Invalidate() override
	{
		InvalidateRect(m_hWnd, nullptr, false);
	}

	void SetTitle(const std::wstring& title) override
	{
		SetWindowText(m_hWnd, title.c_str());
	}

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_Width = CW_USEDEFAULT;
	int m_Height = CW_USEDEFAULT;

	std::vector<uint8_t> m_SurfaceMemory;
};

std::unique_ptr<IPlatformWindow> CreatePlatformWindow(IApplication* application)
{
	return std::make_unique<PlatformWindow_Win>(application);
}