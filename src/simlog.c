#ifndef SIMLOG_C
#define SIMLOG_C
#include<stdio.h>
#include<time.h>
#define SIMLOG_BUFFER = 1024
#define SIMLOG_INFO 1
#define SIMLOG_WARN 2
#define SIMLOG_ERROR 3
#define TFLEN 21
const char* SIMLOG_INFO_PREFIX = "INFO";
const char* SIMLOG_WARN_PREFIX = "WARN";
const char* SIMLOG_ERROR_PREFIX = "ERROR";

FILE *logfp;

void simlog_write(char *message, int type) {
    assert(logfp != NULL);
    
    if (logfp == NULL) return;
    const char *prefix;
    time_t curtime;
    struct tm *loc_time;
    char formatted_date[TFLEN];
    switch(type) {
        case SIMLOG_INFO: prefix = SIMLOG_INFO_PREFIX; break;
        case SIMLOG_WARN: prefix = SIMLOG_WARN_PREFIX; break;
        case SIMLOG_ERROR: prefix = SIMLOG_ERROR_PREFIX; break;
        default: prefix = "[???]"; break;
    }

    //Getting current time of system
    curtime = time (NULL);
    
    // Converting current time to local time
    loc_time = localtime (&curtime);

    strftime(formatted_date, TFLEN, "%Y-%m-%d %H:%M:%S", loc_time);

    fprintf(logfp, "[%s][%19s]%s\n", prefix, formatted_date, message);
}

#define info(message) simlog_write(message, SIMLOG_INFO);
#define warn(message) simlog_write(message, SIMLOG_WARN);
#define error(message) simlog_write(message, SIMLOG_ERROR);

#endif