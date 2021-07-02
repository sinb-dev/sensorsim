#include <assert.h>
#include <unistd.h>

#include "simlog.c"
#include "netcode.c"
#include "sensorsim.c"
#include "export.c"


//Non-blocking keyboard read
int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

void flushbuffer()
{
    export();
    netsend("Oh hai there");
    buf_pos = 0;
}

void mainloop(void) 
{   
    
    size_t duration = 1000000;
    int cycle_mksec = 40;

    printf("Starting main loop\n");
    for (size_t time = 0; time < duration; time+=cycle_mksec) {
        unsigned short val = getreading(time);
        buf_readings[buf_pos] = val;
        buf_timetamps[buf_pos] = time;
        buf_rpms[buf_pos] = getrpm(time);
        if (buf_pos >= BUFFERSIZE) {
            flushbuffer();
        } else {
            buf_pos++;
        }
    }
    printf("Completed\n");

}

int main(void)
{
    logfp = fopen("sim.log", "a");
    if (logfp == NULL)
    {
        fprintf(stderr, "Failed to open sim.log for writing.\n");
        return EXIT_FAILURE;
    }

    srand(100);
    
    mainloop();

    assert(logfp != NULL)
    fclose(logfp);
    
    assert(exportfp != NULL)
    fclose(exportfp);
    
    return EXIT_SUCCESS;
}