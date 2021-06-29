#ifndef SENSORSIM_C
#define SENSORSIM_C

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "netcode.c"
#include "random.c"

unsigned short white_noise(size_t microsecond)
{
  return random_ushort(microsecond) % 255;
}

unsigned short harmonics_peak(size_t microsecond)
{
    double parable_x = round(microsecond / 400.0) * 400;
    double x = microsecond - parable_x;
    double a = -16.5;
    double b = 0;
    double c = 1024;

    double y = a*x*x + b*x + c;
    return y > 0 ? y : 0;
}

unsigned short getreading(size_t microsecond)
{
    unsigned short value = 0;
    //Random white noise 
    value += white_noise(microsecond);
    //Harmonic peaks are not dangerous. They are natural and expected.
    value += harmonics_peak(microsecond);
    return value;
}

#endif