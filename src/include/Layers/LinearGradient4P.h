#pragma once

#include "BaseLayer.h"
#include "include/effects/SkRuntimeEffect.h"

class LinearGradient4P final : public BaseLayer
{
public:
	LinearGradient4P();
	~LinearGradient4P() override = default;

	SkString GetTitle() const override { return SkString{"4P Linear Gradient"}; };
	void onPaint(SkSurface* surface) override;

private:
	sk_sp<SkData> GetUniforms(SkCanvas* canvas) const;
	
	sk_sp<SkRuntimeEffect> m_Effect;
};
