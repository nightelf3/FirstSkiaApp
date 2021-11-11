#include "include/Interfaces/IPlatformWindow.h"
#include "include/Interfaces/IBackground.h"

#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <map>

namespace
{
	constexpr TCHAR g_sWindowClass[] = _T("FirstSkiaApp");

	ModifierKey get_modifiers()
	{
		ModifierKey modifiers = ModifierKey::kNone;
		if (GetAsyncKeyState(VK_LCONTROL) & 0x8000) {
			modifiers |= ModifierKey::kControl;
		}
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
			modifiers |= ModifierKey::kShift;
		}
		return modifiers;
	}

	Key get_key(WPARAM vk)
	{
		static const std::map<WPARAM, Key> gPair{
			{VK_RETURN, Key::kEnter},
			{VK_UP, Key::kUp},
			{VK_DOWN, Key::kDown},
			{VK_LEFT, Key::kLeft},
			{VK_RIGHT, Key::kRight},
			{VK_TAB, Key::kTab},
			{VK_DELETE, Key::kDelete},
			{VK_ESCAPE, Key::kEscape},
			{'X', Key::kX},
			{'Z', Key::kZ}
		};

		auto it = gPair.find(vk);
		return it != gPair.end() ? it->second : Key::kUnknown;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	IApplication* app = reinterpret_cast<IApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (!app)
		return DefWindowProc(hWnd, message, wParam, lParam);

	bool eventHandled = false;
	switch (message)
	{
	case WM_PAINT:
	{
		app->OnPaint();
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
		app->OnResize(LOWORD(lParam), HIWORD(lParam));
		eventHandled = true;
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		eventHandled = app->OnKey(get_key(wParam), InputState::kDown, get_modifiers());
		if (eventHandled)
			app->Invalidate();
		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		eventHandled = app->OnKey(get_key(wParam), InputState::kUp, get_modifiers());
		if (eventHandled)
			app->Invalidate();
		break;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP: {
		const int xPos = GET_X_LPARAM(lParam);
		const int yPos = GET_Y_LPARAM(lParam);
		const InputState iState = ((wParam & MK_LBUTTON) != 0) ? InputState::kDown : InputState::kUp;
		eventHandled = app->OnMouse(xPos, yPos, iState, get_modifiers());
		if (eventHandled)
			app->Invalidate();
		break;
	}

	case WM_MOUSEMOVE: {
		const int xPos = GET_X_LPARAM(lParam);
		const int yPos = GET_Y_LPARAM(lParam);
		eventHandled = app->OnMouse(xPos, yPos, InputState::kMove, get_modifiers());
		if (eventHandled)
			app->Invalidate();
		break;
	}

	case WM_MOUSEWHEEL:
		eventHandled = app->OnMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? InputState::kZoomIn : InputState::kZoomOut, get_modifiers());
		if (eventHandled)
			app->Invalidate();
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
			CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, m_hInstance, nullptr);
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
		if (m_Background)
			m_Background->SwapBuffers();
	}

	sk_sp<SkSurface> Resize(int width, int height) override
	{
		if (!m_Background)
			return nullptr;

		m_Background->Destroy();
		return m_Background->CreateSurface(width, height);
	}

	void Invalidate() override
	{
		InvalidateRect(m_hWnd, nullptr, false);
	}

	void SetTitle(const std::wstring& title) override
	{
		SetWindowText(m_hWnd, title.c_str());
	}

	const IBackground* GetBackgound() const override
	{
		return m_Background.get();
	}

	sk_sp<SkSurface> SetBackgound(std::unique_ptr<IBackground>&& background) override
	{
		m_Background = std::move(background);
		if (!m_Background)
			return nullptr;

		RECT rect;
		GetClientRect(GetHandle(), &rect);
		return m_Background->CreateSurface(rect.right - rect.left, rect.bottom - rect.top);
	}

	WHandle GetHandle() const override
	{
		return m_hWnd;
	}

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	std::unique_ptr<IBackground> m_Background;
};

std::unique_ptr<IPlatformWindow> CreatePlatformWindow(IApplication* application)
{
	return std::make_unique<PlatformWindow_Win>(application);
}