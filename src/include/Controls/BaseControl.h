#pragma once

#include "include/Interfaces/IControl.h"
#include "include/core/SkString.h"

class BaseControl : public IControl
{
public:
	BaseControl(SkString caption = {});
	~BaseControl() override;

	void Draw(SkCanvas* canvas, const SkRect& bounds) override { m_Bounds = bounds; }
	bool ProcessMouse(int x, int y, InputState state, ModifierKey modifiers) override;

protected:
	bool IsActive() const { return m_Active; }
	SkRect GetBounds() const { return m_Bounds; }
	const SkString& GetCaption() const { return m_Caption; }

	virtual bool IsSupportInputState(InputState state) const;
	virtual bool OnMouseDown(int x, int y, ModifierKey modifiers) { return false; }
	virtual void OnMouseMove(int x, int y, ModifierKey modifiers, bool active) {}
	virtual void OnMouseUp(int x, int y, ModifierKey modifiers) {}

private:
	const SkString m_Caption;
	SkRect m_Bounds{};

	bool m_Active = false;
	bool m_MouseDown = false;
};
