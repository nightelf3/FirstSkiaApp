#pragma once

#include "include/Interfaces/IControl.h"
#include <vector>

class ControlsContainer : public IControl
{
public:
	~ControlsContainer() override = default;

	template<typename T, class... TArgs>
	std::weak_ptr<T> AddControl(TArgs&&... args)
	{
		auto control = std::make_shared<T>(std::forward<TArgs>(args)...);
		m_Controls.push_back(control);
		return control;
	}

	void Draw(SkCanvas* canvas, const SkRect& bounds) override;
	bool ProcessKey(Key key, InputState state, ModifierKey modifiers) override;
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override;
	SkScalar GetHeight() const override;

private:
	SkRect GetPanelRect(const SkRect& bounds) const;

	std::vector<std::shared_ptr<IControl>> m_Controls;
};
