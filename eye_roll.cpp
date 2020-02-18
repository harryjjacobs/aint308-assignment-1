#include "eye_roll.h"
#include "owl-pwm.h"
#include <math.h>
#include <chrono>


#define ROLL_SPEED 10.0
#define FREQ 1 / ROLL_SPEED

#define PI 3.14159265

using namespace std::chrono;

void eye_roll(int& rx, int& ry, int& lx, int& ly)
{
    // Get current time in ms
    auto millis = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    // Calculate theta from angular frequency * time
    double t = 2.0 * PI * FREQ * (millis / 1000.0);
    // Move x and y in circular pattern at given frequency
    rx = static_cast<int>(RxLm  +  ((RxRm - RxLm)) * (sin(t) + 1) / 2.0);
    ry = static_cast<int>(RyBm  +  ((RyTm - RyBm)) * (cos(t) + 1) / 2.0);
    // Move x and y in circular pattern at given frequency
    lx = static_cast<int>(LxLm  +  ((LxRm - LxLm)) * (sin(t) + 1) / 2.0);
    ly = static_cast<int>(LyBm  -  ((LyBm - LyTm)) * (cos(t) + 1) / 2.0);
}
