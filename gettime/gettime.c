#include <stdlib.h>
#include <sys/time.h>

struct timeval tv[2];

double gettime(int flag)
{
    gettimeofday(&tv[flag],NULL);
    return tv[flag].tv_sec%1000 + tv[flag].tv_usec/1000000.0;
}
