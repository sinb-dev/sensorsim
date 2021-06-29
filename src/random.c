#ifndef RANDOM_C
#define RANDOM_C

#include "random_raw/random_raw.c"

static inline char random_char(size_t time)
{
  return random_data[time % RANDOM_DATA_SIZE];
}

static inline int8_t random_int8(size_t time)
{
  return (int8_t)random_char(time);
}

static inline uint8_t random_uint8(size_t time)
{
  return (uint8_t)random_char(time);
}

#endif
