#ifndef RANDOM_C
#define RANDOM_C

#include <assert.h>
#include <stdint.h>

#include "random_raw/random_raw.c"

static inline char random_char(size_t time)
{
  return random_data[time % RANDOM_DATA_SIZE];
}

static inline uint8_t random_uint8(size_t time)
{
  assert (sizeof(char) == 1);
  return (uint8_t)random_char(time);
}

static inline uint16_t random_uint16(size_t time)
{
  return ((uint16_t)random_uint8(time) << 8) | random_uint8(time+1);
}

static inline uint32_t random_uint32(size_t time)
{
  return ((uint32_t)random_uint16(time) << 16) | random_uint16(time+2);
}

static inline uint64_t random_uint64(size_t time)
{
  return ((uint64_t)random_uint32(time) << 32) | random_uint32(time+4);
}

static inline unsigned short random_ushort(size_t time)
{
  if (sizeof(unsigned short) == 1) return random_uint8(time);
  if (sizeof(unsigned short) == 2) return random_uint16(time);
  if (sizeof(unsigned short) == 4) return random_uint32(time);
  if (sizeof(unsigned short) == 8) return random_uint64(time);
  assert(0);
}

#endif
