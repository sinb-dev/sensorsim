#ifndef SENSORSIM_C
#define SENSORSIM_C

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "netcode.c"
#include "random.c"

struct timeval start;

unsigned short white_noise(size_t microsecond)
{
  return random_ushort(microsecond);
}

unsigned short anomaly_parabel(size_t microsecond)
{
    double parable_x = round(microsecond / 200.0) * 200;
    double x = microsecond - parable_x;
    double a = -16.0;
    double b = 0;
    double c = 1024;

    double y = a*x*x + b*x + c;
    return y > 0 ? y : 0;
}

unsigned short getreading(size_t microsecond)
{
    unsigned short value = 0;
    value += white_noise(microsecond);
    value += anomaly_parabel(microsecond);
    return value;
}

#endif