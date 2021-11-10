#pragma once

#include "include/Interfaces/IControl.h"
#include <vector>

class ControlsContainer : public IControl
{
public:
	template<typename T, class... TArgs>
	std::weak_ptr<IControlValue> AddControl(TArgs&&... args)
	{
		m_Controls.push_back(std::make_shared<T>(std::forward<TArgs>(args)...));
		return m_Controls.back();
	}

	void Draw(SkCanvas* canvas, const SkRect& bounds) override;
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override;
	SkScalar GetHeight() const override;

private:
	SkRect GetPanelRect(const SkRect& bounds) const;

	std::vector<std::shared_ptr<IControlValue>> m_Controls;
};
