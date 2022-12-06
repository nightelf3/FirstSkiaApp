#pragma once

#include "BaseLayer.h"
#include "include/effects/SkRuntimeEffect.h"

class SimpleLinearGradient final : public BaseLayer
{
public:
	SimpleLinearGradient();
	~SimpleLinearGradient() override = default;

	SkString GetTitle() const override { return SkString{"Simple Linear Gradient"}; };
	void onPaint(SkSurface* surface) override;

private:
	sk_sp<SkRuntimeEffect> m_Effect;
};
