#pragma once

#include "include/Interfaces/IControl.h"
#include "include/Interfaces/IControlCaption.h"
#include "include/core/SkString.h"

class BaseControl : public IControl, public IControlCaption
{
public:
	BaseControl(SkString caption = {});
	~BaseControl() override;

	const SkString& GetCaption() const override { return m_Caption; }
	void SetCaption(SkString caption) override { m_Caption = std::move(caption); }

	void Draw(SkCanvas* canvas, const SkRect& bounds) override { m_Bounds = bounds; }

	virtual bool ProcessChar(SkUnichar c, skui::ModifierKey modifiers) override final;
	virtual bool ProcessKey(skui::Key key, skui::InputState state, skui::ModifierKey modifiers) override final;
	virtual bool ProcessMouse(int x, int y, skui::InputState state, skui::ModifierKey modifiers) override final;

protected:
	bool IsActive() const { return m_Active; }
	SkRect GetBounds() const { return m_Bounds; }

	virtual bool OnChar(SkUnichar c, skui::ModifierKey modifiers) { return false; }
	virtual bool OnKey(skui::Key key, skui::InputState state, skui::ModifierKey modifiers) { return false; }

	virtual bool IsSupportInputState(skui::InputState state) const;
	virtual bool OnMouseDown(int x, int y, skui::ModifierKey modifiers) { return false; }
	virtual void OnMouseMove(int x, int y, skui::ModifierKey modifiers, bool active) {}
	virtual void OnMouseUp(int x, int y, skui::ModifierKey modifiers) {}

private:
	SkString m_Caption;
	SkRect m_Bounds{};

	bool m_Active = false;
	bool m_MouseDown = false;
};
