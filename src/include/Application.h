#ifndef APPLICAITON_H_79E41F56_5C03_42AE_A084_9058DBDEEE82
#define APPLICAITON_H_79E41F56_5C03_42AE_A084_9058DBDEEE82

#include "Interfaces/IApplication.h"
#include "Interfaces/IPlatformWindow.h"
#include "LayerCollection.h"
#include "include/Utils/FPS.h"

class Application : public IApplication
{
public:
	Application();

	void Show() override;
	void AddLayer(spLayer&& layer) override;
	void OnPaint() override;
	void OnIdle() override;
	void OnResize(int w, int h) override;
	bool OnKey(Key key, InputState state, ModifierKey modifiers) override;
	bool OnMouse(int x, int y, InputState state, ModifierKey modifiers) override;

	void Invalidate() override;
	void SwapBuffers() override;

private:
	void ChangeBackgound(std::unique_ptr<IBackground>&& backgound);
	void UpdateTitle();

	std::unique_ptr<IPlatformWindow> m_Window;
	LayerCollection m_Layers;
	sk_sp<SkSurface> m_Surface;
	FPS m_FPS;
};

#endif // APPLICAITON_H_79E41F56_5C03_42AE_A084_9058DBDEEE82
