#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "netcode.c"
struct Sensorsim {
    struct timeval start
} sensorsim;

char getreading(unsigned long microsecond)
{
    return rand() % 255;
}