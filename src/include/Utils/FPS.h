#pragma once

#include "include/Layers/BaseLayer.h"
#include <chrono>

using std::chrono::system_clock;
using std::chrono::time_point;

class FPS
{
public:
	void Calc();
	void Draw(SkCanvas* canvas);
	SkString Get() const;

private:
	time_point<system_clock> m_LastCalc = system_clock::now();
	double m_FPS = 0.0;
};
