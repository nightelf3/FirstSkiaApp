#pragma once

#include "include/Types.h"
#include "include/Interfaces/ILayer.h"

class BaseLayer : public ILayer
{
public:
	~BaseLayer() override = default;
	std::wstring GetTitle() const override { return L""; };
	bool ProcessKey(Key key, InputState state, ModifierKey modifiers) override { return false; }
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override { return false; }
	bool ProcessMouseWheel(InputState state, ModifierKey modifiers) override { return false; }
};
