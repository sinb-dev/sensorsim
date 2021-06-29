
#ifndef EXPORT_C
#define EXPORT_C
#include<stdio.h>

FILE *exportfp = NULL;

void export()
{
    if (exportfp == NULL) {
        exportfp = fopen("data.csv", "w");
    }
    
    for (int i = 0; i < BUFFERSIZE; i++) {
        fprintf(exportfp, "%lu;%hu;\n", buf_timetamps[i], buf_readings[i]);
    }

    fprintf(exportfp, "\n");
    for (int i = 0; i < BUFFERSIZE; i++) {
    }

    //for (size_t time = 0; time < 1000; time++) {
        //unsigned short val = getreading(time);
        //fprintf(exportfp, "%hu;", val);
    //}

    fclose(exportfp);
}

#endif