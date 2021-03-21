#ifndef THANKYOULAYER_H_FA0B7C58_974B_45F1_88AA_77F52097B75C
#define THANKYOULAYER_H_FA0B7C58_974B_45F1_88AA_77F52097B75C

#include "BaseLayer.h"
#include <chrono>

using std::chrono::system_clock;
using std::chrono::time_point;

class ThankYouLayer final : public BaseLayer
{
public:
	ThankYouLayer();
	std::wstring GetTitle() const override { return L"Thank you for attention"; };
	void Draw(SkCanvas* canvas) override;
	bool IsDrawOnIdle() const override { return true; }

private:
	std::array<sk_sp<SkImage>, 4> m_Images;
	size_t m_Current = 0;
	time_point<system_clock> m_LastDraw = system_clock::now();
};

#endif // THANKYOULAYER_H_FA0B7C58_974B_45F1_88AA_77F52097B75C
