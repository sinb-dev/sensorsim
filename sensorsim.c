#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

struct Sensorsim {
    struct timeval start
} sensorsim;

char getreading(unsigned long microsecond)
{
    return rand() % 255;
}

//Non-blocking keyboard read
int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

void mainloop(void) 
{
    gettimeofday(&sensorsim.start, NULL);
    struct timeval now;
    
    unsigned long freq = 0;

    while(1)
    {
        sleep(0.00004);
        gettimeofday(&now, NULL);
        long delta = now.tv_sec * 1000000 + now.tv_usec 
            - sensorsim.start.tv_sec * 1000000 + sensorsim.start.tv_usec;

        char r = getreading(delta);

        if(kbhit())
        {
            break;
        }
        freq++;
    }

    int delta = now.tv_sec - sensorsim.start.tv_sec;
    int cycles_per_sec = freq/delta;
    printf("Reached %ld cycles in %d seconds. Speed: %d", freq, delta, cycles_per_sec);
}

int main(void)
{
    srand(100);
    //int rand = 
    time_t seconds = time (NULL);
    time_t b = time (NULL);
    mainloop();
    //printf("test %d\n",sensorsim.start.tv_usec);
    
    return 0;
}


