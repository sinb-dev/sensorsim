#ifndef BUFFER_C
#define BUFFER_C
#define BUFFERSIZE 1024
#include<stdio.h>

struct timeval start;

unsigned short buf_readings[BUFFERSIZE];
size_t buf_timetamps[BUFFERSIZE];
int buf_pos = 0;
#endif