#include "include/core/SkTypes.h"
#include "include/Application.h"

#include "include/Backgounds/RasterBackgound.h"
#include "include/Backgounds/OpenGLBackgound.h"

Application::Application()
{
	m_Window = CreatePlatformWindow(this);
	m_Window->SetBackgound(std::make_unique<OpenGLBackgound>(m_Window->GetHandle()));
}

void Application::Show()
{
	UpdateTitle();
	m_Window->Show();
}

void Application::AddLayer(spLayer&& layer)
{
	if (!layer)
		return;
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

	m_FPS.Calc();
	UpdateTitle();
}

void Application::OnIdle()
{
	Invalidate();
}

void Application::OnResize(int w, int h)
{
	m_Surface = m_Window->Resize(w, h);
}

bool Application::OnKey(Key key, InputState state, ModifierKey modifiers)
{
	switch (key)
	{
	case Key::kTab:
		if (InputState::kDown != state)
			break;

		if (ModifierKey::kNone == modifiers)
			m_Layers.Next();
		else if (ModifierKey::kShift == modifiers)
			m_Layers.Prev();
		UpdateTitle();
		return true;

	case Key::kZ:
		if (InputState::kDown != state)
			break;
		ChangeBackgound(std::make_unique<RasterBackgound>(m_Window->GetHandle()));
		return true;

	case Key::kX:
		if (InputState::kDown != state)
			break;
		ChangeBackgound(std::make_unique<OpenGLBackgound>(m_Window->GetHandle()));
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

void Application::ChangeBackgound(std::unique_ptr<IBackground>&& backgound)
{
	m_Surface = m_Window->SetBackgound(std::move(backgound));
	UpdateTitle();
}

void Application::UpdateTitle()
{
	std::wstring title;
	if (auto background = m_Window->GetBackgound())
	{
		title.append(m_Window->GetBackgound()->GetName());
		title.append(L" - ");
	}

	if (auto layer = m_Layers.Active())
	{
		title.append(layer->GetTitle());
		title.append(L" - ");
	}

	const SkString fps = m_FPS.Get();
	title.append(std::wstring(fps.c_str(), fps.c_str() + strlen(fps.c_str())));

	m_Window->SetTitle(std::move(title));
}
