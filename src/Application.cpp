#include "tools/sk_app/Application.h"
#include "tools/sk_app/Window.h"

#include "include/core/SkGraphics.h"

#include "include/Utils/IterableCollection.h"
#include "include/Utils/FPS.h"
#include "include/Layers/SwirlLayer.h"
#include "include/Layers/BlackAndWhiteLayer.h"

using namespace sk_app;

bool gCheckErrorGL = false;
bool gLogCallsGL = false;

class FirstSkiaApp : public sk_app::Application, sk_app::Window::Layer
{
public:
	FirstSkiaApp(int argc, char** argv, void* platformData);
	~FirstSkiaApp() override;
	void onIdle() override;

	void onBackendCreated() override;
	void onPaint(SkSurface* surface) override;
	bool onChar(SkUnichar c, skui::ModifierKey modifiers) override;
	bool onKey(skui::Key key, skui::InputState state, skui::ModifierKey modifiers) override;
	bool onMouse(int x, int y, skui::InputState state, skui::ModifierKey modifiers) override;

private:
	void updateTitle();

	std::unique_ptr<sk_app::Window> m_Window;

	IterableCollection<std::shared_ptr<BaseLayer>> m_Layers;
	IterableCollection<sk_app::Window::BackendType> m_Backends;
	FPS m_FPS;
};

FirstSkiaApp::FirstSkiaApp(int argc, char** argv, void* platformData)
{
	SkGraphics::Init();
	SkGraphics::AllowJIT();

	m_Window.reset(Window::CreateNativeWindow(platformData));
	m_Window->setRequestedDisplayParams(DisplayParams());

	m_Layers.Add(std::make_shared<SwirlLayer>());
	m_Layers.Add(std::make_shared<BlackAndWhiteLayer>());

	m_Backends.Add(Window::kNativeGL_BackendType);
	m_Backends.Add(Window::kRaster_BackendType);

	// register callbacks
	m_Window->pushLayer(this);
	m_Window->attach(m_Backends.Active());
}

FirstSkiaApp::~FirstSkiaApp()
{
	m_Window->detach();
}

void FirstSkiaApp::onBackendCreated()
{
	updateTitle();
	m_Window->show();
	m_Window->inval();
}

void FirstSkiaApp::onIdle()
{
	// re-paint continously
	m_Window->inval();

	m_FPS.Calc();
	updateTitle();
}

void FirstSkiaApp::onPaint(SkSurface* surface)
{
	if (auto layer = m_Layers.Active())
		layer->onPaint(surface);
}

bool FirstSkiaApp::onChar(SkUnichar c, skui::ModifierKey modifiers)
{
	if (' ' == c)
	{
		if (skui::ModifierKey::kShift == (modifiers & skui::ModifierKey::kShift))
			m_Backends.Prev();
		else
			m_Backends.Next();
		m_Window->detach();
		m_Window->attach(m_Backends.Active());
		return true;
	}

	if ('\t' == c)
	{
		if (skui::ModifierKey::kShift == (modifiers & skui::ModifierKey::kShift))
			m_Layers.Prev();
		else
			m_Layers.Next();
		m_Window->inval();
		return true;
	}

	if (auto layer = m_Layers.Active())
		return layer->onChar(c, modifiers);

	return false;
}

bool FirstSkiaApp::onKey(skui::Key key, skui::InputState state, skui::ModifierKey modifiers)
{
	if (auto layer = m_Layers.Active())
		return layer->onKey(key, state, modifiers);
	return false;
}

bool FirstSkiaApp::onMouse(int x, int y, skui::InputState state, skui::ModifierKey modifiers)
{
	if (auto layer = m_Layers.Active())
		return layer->onMouse(x, y, state, modifiers);
	return false;
}

void FirstSkiaApp::updateTitle()
{
	if (!m_Window)
		return;

	SkString title;
	title.append(Window::kRaster_BackendType == m_Backends.Active() ? "Raster" : "OpenGL");
	title.append(" - ");

	if (auto layer = m_Layers.Active())
	{
		title.append(layer->GetTitle());
		title.append(" - ");
	}

	title.append(m_FPS.Get());

	m_Window->setTitle(title.c_str());
}


Application* sk_app::Application::Create(int argc, char** argv, void* platformData)
{
	return new FirstSkiaApp(argc, argv, platformData);
}
