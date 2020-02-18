#include "annoyed_eye_roll.h"
#include "owl-pwm.h"
#include <math.h>
#include <chrono>

#define ROLL_SPEED 2.0
#define FREQ 1 / ROLL_SPEED
#define PI 3.14159

// Start times and durations of the different 'actions'
#define ACT1_START      (0.0)
#define ACT1_DURATION   (250.0)
#define ACT2_START      (ACT1_START + ACT1_DURATION)
#define ACT2_DURATION   (750.0)
#define ACT3_START      (ACT2_START + ACT2_DURATION)
#define ACT3_DURATION   (250.0)
#define ACT4_START      (ACT3_START + ACT3_DURATION)
#define ACT4_DURATION   (750.0)
#define ACT5_START      (ACT4_START + ACT4_DURATION)
#define ACT5_DURATION   (1000.0)
#define ACT_ALL         (ACT5_START + ACT5_DURATION)

using namespace std::chrono;

static long long last_time = 0;
static int counter = 0;

void annoyed_eye_roll(int& rx, int& ry, int& lx, int& ly, int& neck)
{
    auto millis = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();  // Get current time in ms
    int delta = static_cast<int>(millis - last_time);                                           // Time since last time function was called
    last_time = millis;                                                                         // Record current time

    counter += delta;                                                                           // Increase counter every time function is called in loop

    if (counter >= ACT_ALL)
    {
        // Reset counter every time we reach the end of the actions
        counter = 0;
        // Center everthing before starting
        rx = RxC; Lx = LxC;
        ry = RyC; Ly = LyC;
        neck = NeckC;
    }
    else if (counter > ACT1_START && counter <= ACT2_START)  // Determine if counter within action 1 duration
    {
        // Move both eyes in the positive Y directionpan both eyes
        ry = static_cast<int>(RyC + (counter / 1000.0) * (RyTm - RyC));
        ly = static_cast<int>(LyC - (counter / 1000.0) * (LyC - LyTm));
    }
    else if (counter > ACT2_START && counter <= ACT3_START) // Sets Action 2 duration
    {
        double t = (counter - ACT2_START) / ACT2_DURATION;
        // Calculate theta from angular frequency * time
        double theta = 2.0 * PI * FREQ * t;
        neck = static_cast<int>(NeckC + t * (NeckL  - NeckC) / 4);  // Pans the neck slightly
        rx = static_cast<int>(RxC  -  ((RxC - RxLm)) * (sin(theta) + 1) / 2.0); // Move both eyes in clockwise direction for 90 degrees.
        ry = static_cast<int>(RyTm  -  ((RyTm - RyC)) * (-cos(theta) + 1) / 2.0);

        lx = static_cast<int>(LxC  -  ((LxRm - LxC)) * (sin(theta) + 1) / 2.0);
        ly = static_cast<int>(LyTm  +  ((LyC - LyTm)) * (-cos(theta) + 1) / 2.0);
    }
    else if (counter > ACT3_START && counter <= ACT4_START)                                      //Sets Action 3 duration
    {
        // delay
    }
    else if (counter > ACT4_START && counter <= ACT5_START)                                      //Sets Action 4 duration
    {
        double t = (counter - ACT4_START) / ACT4_DURATION;

        neck = static_cast<int>(NeckC + (NeckL - NeckC) / 4 - t * (NeckL - NeckC) / 4);     //Return neck to center position

        rx = static_cast<int>(RxLm + t * (RxC - RxLm));                                     //return eyes to center position

        lx = static_cast<int>(LxLm + t * (LxC - LxLm));
    }
    else if (counter > ACT5_START && counter <= ACT_ALL)                                         //Sets Action 5 duration
    {
        // delay
    }
}
