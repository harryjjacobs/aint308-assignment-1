#include "point_focus.h"
#include <math.h>
#include "owl-pwm.h"
#include <chrono>

#define SIN_FREQ 1 / 10.0
#define PI 3.14159265

using namespace std::chrono;

void point_focus(int& rx, int& lx, int& neck)
{
    auto millis = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    double sin_t = (sin(2.0 * PI * SIN_FREQ * (millis / 1000.0)) + 1) / 2.0;

    neck = static_cast<int>(NeckR + ((NeckL - NeckR)) * sin_t);
    if (neck > NeckL)
    {
        neck = NeckL;
    }

    //adjust eye pos on x axis
    rx = static_cast<int>(RxRangeM * sin_t + RxLm);
    lx = static_cast<int>(LxRangeM * sin_t + LxLm);
}
