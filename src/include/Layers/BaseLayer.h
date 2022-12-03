#pragma once

#include "tools/sk_app/Window.h"

class BaseLayer : public sk_app::Window::Layer
{
public:
	~BaseLayer() override = default;
	virtual SkString GetTitle() const { return {}; };
};
