#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../sensorsim.c"

LARGE_INTEGER qp_freq, qp_start, qp_stop;

static inline void stopwatch_init()
{
  QueryPerformanceFrequency(&qp_freq);
}

static inline void stopwatch_start()
{
  QueryPerformanceCounter(&qp_start);
}

static inline void stopwatch_stop()
{
  QueryPerformanceCounter(&qp_stop);
}

static inline size_t stopwatch_us()
{
  return (qp_stop.QuadPart - qp_start.QuadPart) * 1000000 / qp_freq.QuadPart;
}

#define SAMPLE_SIZE 20000000
unsigned short data[SAMPLE_SIZE];

static void indent(unsigned int num)
{
  for(unsigned int i = 0; i < num; ++i)
  {
    printf(" ");
  }
}

#define RIGHT_JUSTIFICATION 40

static void print_sample_result(int x)
{
  for(int i = x; i < RIGHT_JUSTIFICATION; ++i) printf(" ");
  printf("%u us\n", stopwatch_us());
}

int main()
{
  printf("Sample size: %u\n\n", SAMPLE_SIZE);
  stopwatch_init();



  printf("white_noise:");
  for(size_t i = 0; i < SAMPLE_SIZE; ++i)
  {
    data[i] = white_noise(i);
  }
  stopwatch_start();
  for(size_t i = 0; i < SAMPLE_SIZE; ++i)
  {
    data[i] = white_noise(i);
  }
  stopwatch_stop();
  print_sample_result(12);



  printf("harmonics_peak:");
  for(size_t i = 0; i < SAMPLE_SIZE; ++i)
  {
    data[i] = harmonics_peak(i);
  }
  stopwatch_start();
  for(size_t i = 0; i < SAMPLE_SIZE; ++i)
  {
    data[i] = harmonics_peak(i);
  }
  stopwatch_stop();
  print_sample_result(15);



  printf("\ngetreading:");
  for(size_t i = 0; i < SAMPLE_SIZE; ++i)
  {
    data[i] = getreading(i);
  }
  stopwatch_start();
  for(size_t i = 0; i < SAMPLE_SIZE; ++i)
  {
    data[i] = getreading(i);
  }
  stopwatch_stop();
  print_sample_result(11);



  double time_25000 = stopwatch_us() * 25000 / (double)SAMPLE_SIZE;
  printf("\nEstimate time for 25000 samples: %.2f ms.\n", time_25000 / 1000);

  return 0;
}
