#ifndef EXPORT_C
#define EXPORT_C
#include<stdio.h>
#include "buffer.c"

FILE *exportfp = NULL;

void export()
{
    if (exportfp == NULL) {
        exportfp = fopen("data.csv", "w");
        fprintf(exportfp, "time,reading\n");
    }
    for (int i = 1; i < BUFFERSIZE; i++) {
        fprintf(exportfp, "%lu,%hu\n", buf_timetamps[i], buf_readings[i]);
    }

}


#endif