
#ifndef EXPORT_C
#define EXPORT_C
#include<stdio.h>

FILE *exportfp = NULL;

void export()
{
    if (exportfp == NULL) {
        exportfp = fopen("data.csv", "w");
    }
    
    for (size_t time = 0; time < 1000; time++) {
        unsigned short val = getreading(time);
        fprintf(exportfp, "%hu;", val);
    }
}

#endif