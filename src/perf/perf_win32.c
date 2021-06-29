#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../sensorsim.c"

LARGE_INTEGER qp_freq, qp_start;

static inline void stopwatch_init()
{
  QueryPerformanceFrequency(&qp_freq);
}

static inline void stopwatch_start()
{
  QueryPerformanceCounter(&qp_start);
}

static inline void stopwatch(LARGE_INTEGER* li)
{
  QueryPerformanceCounter(li);
}

static inline size_t stopwatch_us(LARGE_INTEGER* stop)
{
  return (stop->QuadPart - qp_start.QuadPart) * 1000000 / qp_freq.QuadPart;
}

#define RIGHT_JUSTIFICATION 40

typedef struct {
  unsigned short data;
  LARGE_INTEGER timestamp;
} sample_t;

#define SAMPLE_SIZE 25000
sample_t samples[SAMPLE_SIZE];

static void indent(unsigned int num)
{
  for(unsigned int i = 0; i < num; ++i)
  {
    printf(" ");
  }
}

static void print_sample_result(int x)
{
  for(int i = x; i < RIGHT_JUSTIFICATION; ++i) printf(" ");

  size_t min = UINT64_MAX;
  size_t max = 0;
  size_t sum = 0;
  for(int i = 0; i < SAMPLE_SIZE; ++i)
  {
    size_t time = stopwatch_us(&samples[i].timestamp);
    if (time < min) min = time;
    if (time > max) max = time;
    sum += time;
  }
  printf("%uus / %uus / %uus\n", min, sum/25000, max);
}

int main()
{
  printf("Sample size: %u\n\n", SAMPLE_SIZE);
  stopwatch_init();

  printf("white_noise:");
  for(size_t i = 0; i < SAMPLE_SIZE; ++i)
  {
    samples[i].data = white_noise(i);
  }
  stopwatch_start();
  for(size_t i = 0; i < SAMPLE_SIZE; ++i)
  {
    samples[i].data = white_noise(i);
    stopwatch(&(samples[i].timestamp));
  }
  print_sample_result(12);

  printf("harmonics_peak:");
  for(size_t i = 0; i < SAMPLE_SIZE; ++i)
  {
    samples[i].data = harmonics_peak(i);
  }
  stopwatch_start();
  for(size_t i = 0; i < SAMPLE_SIZE; ++i)
  {
    samples[i].data = harmonics_peak(i);
    stopwatch(&(samples[i].timestamp));
  }
  print_sample_result(15);

  printf("\ngetreading:");
  for(size_t i = 0; i < SAMPLE_SIZE; ++i)
  {
    samples[i].data = getreading(i);
  }
  stopwatch_start();
  for(size_t i = 0; i < SAMPLE_SIZE; ++i)
  {
    samples[i].data = getreading(i);
    stopwatch(&(samples[i].timestamp));
  }
  print_sample_result(11);

  return 0;
}
