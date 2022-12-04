#include "philo.h"

long long   timestamp()
{
    struct      timeval tv;
    long        mili;

    gettimeofday(&tv, NULL);
    mili = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (mili);
}

void    ft_usleep(long x)
{
    long    y;

    y = timestamp();
    while (1)
    {
        if (timestamp() - y >= x)
            break;
        usleep(100);
    }
}