#include "chameleon.h"
#include "owl-pwm.h"
#include <random>

#define MOVE_PERCENT 10

int randBetween(int min, int max);

void chameleon_eyes(int& rx, int& ry, int& lx, int& ly)
{
    // Right eye
    if (randBetween(0, 100) < MOVE_PERCENT) // Choose a random position MOVE_PERCENT% of the time
    {
        rx = randBetween(RxLm, RxRm);   // Random position between the two limits
        ry = randBetween(RyBm, RyTm);
    }

    // Left eye
    if (randBetween(0, 100) < MOVE_PERCENT)
    {
        lx = randBetween(LxLm, LxRm);
        ly = randBetween(LyTm, LyBm);
    }
}

int randBetween(int min, int max)
{
    return min + (std::rand() * (max - min)) / RAND_MAX;
}
