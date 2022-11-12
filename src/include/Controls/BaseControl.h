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
	bool ProcessKey(Key key, InputState state, ModifierKey modifiers) override final;
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override final;

protected:
	bool IsActive() const { return m_Active; }
	SkRect GetBounds() const { return m_Bounds; }

	virtual bool OnKey(Key key, InputState state, ModifierKey modifiers) { return false; }

	virtual bool IsSupportInputState(InputState state) const;
	virtual bool OnMouseDown(int x, int y, ModifierKey modifiers) { return false; }
	virtual void OnMouseMove(int x, int y, ModifierKey modifiers, bool active) {}
	virtual void OnMouseUp(int x, int y, ModifierKey modifiers) {}

private:
	SkString m_Caption;
	SkRect m_Bounds{};

	bool m_Active = false;
	bool m_MouseDown = false;
};
