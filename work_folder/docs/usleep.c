//  suspends the current process for the number of microseconds passed to it
// int usleep( useconds_t useconds ); 

#include <unistd.h>

void main()
{
    unsigned int mSeconds = 500000;
    int returnCode;

    returnCode = usleep(mSeconds);
    return;
}  