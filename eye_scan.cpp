#include "eye_scan.h"
#include "owl-pwm.h"

#define EYE_PAN_SPEED 0.05f

static float counter = 0;
static bool countup = false;

void pan_eyes(int& rx, int& lx)
{
    // Adjust eye pos on x axis
    rx = static_cast<int>(RxRangeM * counter + RxLm);
    lx = static_cast<int>(LxRangeM * counter + LxLm);

    // Count up to 1 and then down to 0
    if (countup == true)
    {
        counter += EYE_PAN_SPEED;
        if (counter >= 1)
        {
           countup = false;
        }
    }
    else
    {
        counter -= EYE_PAN_SPEED;
        if (counter <= 0)
        {
            countup = true;
        }
    }
}

