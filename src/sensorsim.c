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
  // Add white noise to the reading as baseline
  unsigned short value = white_noise(microsecond);

  //Add harmonic peaks. These are expected for proper functioning devices.
  value += harmonics_peak(microsecond);

  // The time the device starts malfunctioning.
  size_t malfunction_threshold = random_uint8(0) * 80;

  if (microsecond > malfunction_threshold)
  {
    // Device is old. Introduce pathological behaviour into the simulation.
    size_t malfunction_age = microsecond - malfunction_threshold;

    // The more time has passed since the malfunction threshold, the greater
    // the propability of erratic behaviour in the readings.
    if (random_uint16(microsecond) < malfunction_age) 
    {
      switch(random_uint8(microsecond) & 0x04)
      {
        case 0:
          [[fallthrough]]
        case 1:
          [[fallthrough]]
        case 2:
          value *= 2;
          break;
        case 3:
          value *= 3;
          break;
      }
      
    }
  }

  return value;
}

#endif
