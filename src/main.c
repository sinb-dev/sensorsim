#include "netcode.c"
#include "sensorsim.c"


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
    printf("Reached %ld cycles in %d seconds. Speed: %d readings/sec", freq, delta, cycles_per_sec);
}

int main(void)
{
    srand(100);
    
    mainloop();
    
    return 0;
}