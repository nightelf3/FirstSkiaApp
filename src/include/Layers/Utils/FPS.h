#ifndef FPS_H_8E45E21C_B5A5_44F8_B239_BB6D493A0083
#define FPS_H_8E45E21C_B5A5_44F8_B239_BB6D493A0083

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

#endif // FPS_H_8E45E21C_B5A5_44F8_B239_BB6D493A0083
