#include <math.h>
#include <chrono>
#include "owl-pwm.h"
#include "neck_pan.h"

#define SIN_FREQ 1 / 10.0
#define PI 3.14159265

using namespace std::chrono;

void pan_sin(int& neck)
{
    auto millis = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    neck = static_cast<int>(NeckR  +  ((NeckL - NeckR)) * (sin(2.0 * PI * SIN_FREQ * (millis/1000.0)) + 1) / 2.0);          // Move in sinusoidal motion between the limits of the neck
    if (neck > NeckL)                                                                                                       // Make sure we don't exceed the limit
    {
        neck = NeckL;
    }
}
