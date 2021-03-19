#include "include/core/SkTypes.h"
#include "include/Application.h"

Application::Application()
{
	m_Window = CreatePlatformWindow(this);
	m_Window->Show();
}

void Application::AddLayer(spLayer&& layer)
{
	if (layer)
		m_Layers.Add(std::move(layer));
}

void Application::OnPaint()
{
	if (!m_Surface)
		return;

	// draw into the canvas of this surface
	if (auto layer = m_Layers.Active())
		layer->Draw(m_Surface->getCanvas());

	m_Surface->flushAndSubmit();
	SwapBuffers();
}

void Application::OnIdle()
{
	if (auto layer = m_Layers.Active())
		layer->DrawOnIdle() ? Invalidate() : void();
}

void Application::OnResize(int w, int h)
{
	m_Surface = m_Window->Resize(w, h);
}

bool Application::OnKey(Key key, InputState state, ModifierKey modifiers)
{
	//TODO: change Window name
	switch (key)
	{
	case Key::kLeft:
		if (InputState::kDown == state)
		{
			m_Layers.Prev();
			Invalidate();
		}
		return true;

	case Key::kRight:
		if (InputState::kDown == state)
		{
			m_Layers.Next();
			Invalidate();
		}
		return true;

	default:
		if (auto layer = m_Layers.Active())
			return layer->ProcessKey(key, state, modifiers);
	}

	return false;
}

bool Application::OnMouse(int x, int y, InputState state, ModifierKey modifiers)
{
	if (auto layer = m_Layers.Active())
		return layer->ProcessMouse(x, y, state, modifiers);
	return false;
}

bool Application::OnMouseWheel(InputState state, ModifierKey modifiers)
{
	if (auto layer = m_Layers.Active())
		return layer->ProcessMouseWheel(state, modifiers);
	return false;
}

void Application::Invalidate()
{
	m_Window->Invalidate();
}

void Application::SwapBuffers()
{
	m_Window->Draw();
}