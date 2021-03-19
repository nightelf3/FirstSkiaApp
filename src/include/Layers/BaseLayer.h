#ifndef BASELAYER_H_72BE371C_EC52_49FA_98A0_7C81D0E986F1
#define BASELAYER_H_72BE371C_EC52_49FA_98A0_7C81D0E986F1

#include "include/Types.h"
#include "include/Interfaces/ILayer.h"

class BaseLayer : public ILayer
{
	std::wstring GetTitle() const override { return L""; };
	bool IsDrawOnIdle() const override { return false; }
	bool ProcessKey(Key key, InputState state, ModifierKey modifiers) override { return false; }
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override { return false; }
	bool ProcessMouseWheel(InputState state, ModifierKey modifiers) override { return false; }
};

#endif // BASELAYER_H_72BE371C_EC52_49FA_98A0_7C81D0E986F1
