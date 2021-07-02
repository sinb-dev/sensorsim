#ifndef EXPORT_C
#define EXPORT_C
#include<stdio.h>
#include "buffer.c"

FILE *exportfp = NULL;

// Workaround for printf z-specifier on Windows, because MinGW uses the
// Microsoft C runtime, which only conforms to C89.
#include <inttypes.h>
#ifdef _WIN32
#  ifdef _WIN64
#    define PRINTF_SIZE_T PRIu64
#  else
#    define PRINTF_SIZE_T PRIu32
#  endif
#else
#  define PRINTF_SIZE_T "zu"
#endif

void export()
{
    if (exportfp == NULL) {
        exportfp = fopen("data.csv", "w");
        fprintf(exportfp, "time,reading\n");
    }
    for (int i = 1; i < BUFFERSIZE; i++) {
        fprintf(exportfp, "%" PRINTF_SIZE_T ",%hu\n", buf_timetamps[i], buf_readings[i]);
    }

}


#endif