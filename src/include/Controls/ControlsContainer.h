#pragma once

#include "include/Interfaces/IControl.h"
#include "include/Utils/DrawUtils.h"
#include <vector>

struct ContainerParams
{
	SkScalar width = -1.0f;  // -1.0f means full width
	SkScalar padding = 0.0f;
	SkScalar itemsSpacing = 4.0f;
	DrawUtils::DrawParameters drawParams;
};

class ControlsContainer : public IControl
{
public:
	ControlsContainer(const ContainerParams& params);
	~ControlsContainer() override = default;

	template<typename T, class... TArgs>
	std::weak_ptr<T> AddControl(TArgs&&... args)
	{
		auto control = std::make_shared<T>(std::forward<TArgs>(args)...);
		m_Controls.push_back(control);
		return control;
	}

	void Draw(SkCanvas* canvas, const SkRect& bounds) override;
	bool ProcessChar(SkUnichar c, skui::ModifierKey modifiers) override;
	bool ProcessKey(skui::Key key, skui::InputState state, skui::ModifierKey modifiers) override;
	bool ProcessMouse(int x, int y, skui::InputState state, skui::ModifierKey modifiers) override;
	SkScalar GetHeight() const override;

private:
	SkRect GetPanelRect(SkRect bounds) const;

	ContainerParams m_Params;
	std::vector<std::shared_ptr<IControl>> m_Controls;
};
