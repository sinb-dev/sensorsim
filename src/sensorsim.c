#ifndef SENSORSIM_C
#define SENSORSIM_C

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "netcode.c"
#include "random.c"

// Defines how much white noise the signal has.
#define WHITE_NOISE_AMPLITUDE 255

// Defines how large the harmonic peaks can be.
#define HARMONIC_PEAK_AMPLITUDE 1024

// Defines the distance between harmonic peaks.
#define HARMONIC_PEAK_DISTANCE 400

// Defines the width of the harmonic peaks.
#define HARMONIC_PEAK_WIDTH 16.5

// Defines the minimum age, at which the device begins to fault.
#define MALFUNCTION_THRESHOLD_MINIMUM 0

// Defines how much the malfunction threshold varies from one device to another.
// Bigger equals more variety.
#define MALFUNCTION_THRESHOLD_VARIATION 80

//-------------------------------------------------------------------------//

unsigned short white_noise(size_t microsecond)
{
  return random_ushort(microsecond) % WHITE_NOISE_AMPLITUDE;
}

unsigned short harmonics_peak(size_t microsecond)
{
    double parable_x = round(microsecond / (double)HARMONIC_PEAK_DISTANCE) * HARMONIC_PEAK_DISTANCE;
    double x = microsecond - parable_x;
    double a = -HARMONIC_PEAK_WIDTH;
    double c = HARMONIC_PEAK_AMPLITUDE;

    double y = a*x*x + c;
    return y > 0 ? y : 0;
}

unsigned short getreading(size_t microsecond)
{
  // Add white noise to the reading as baseline
  unsigned short value = white_noise(microsecond);

  //Add harmonic peaks. These are expected for proper functioning devices.
  value += harmonics_peak(microsecond);

  // The time the device starts malfunctioning.
  size_t malfunction_threshold = MALFUNCTION_THRESHOLD_MINIMUM + random_uint8(0) * MALFUNCTION_THRESHOLD_VARIATION;

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
          __attribute__((fallthrough));
        case 1:
          __attribute__((fallthrough));
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
