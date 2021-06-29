
#ifndef EXPORT_C
#define EXPORT_C
#include<stdio.h>

FILE *exportfp = NULL;

void export()
{
    if (exportfp == NULL) {
        exportfp = fopen("data.csv", "w");
    }
    
    for (unsigned long mksec = 0; mksec < 1000; mksec++) {
        unsigned short val = getreading(mksec);
        fprintf(exportfp, "%hu;", val);
    }
}

#endif