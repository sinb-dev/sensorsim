#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

LARGE_INTEGER freq, start, stop;

static inline void stopwatch_init()
{
  QueryPerformanceFrequency(&freq);
}

static inline void stopwatch_start()
{
  QueryPerformanceCounter(&start);
}

static inline void stopwatch_stop()
{
  QueryPerformanceCounter(&stop);
}

static inline size_t stopwatch_us()
{
  return (stop.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;
}

int main()
{
  stopwatch_init();

  stopwatch_start();
  Sleep(100);
  stopwatch_stop();

  return 0;
}