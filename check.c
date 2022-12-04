#include "philo.h"

int    check_died_n(t_info *philo_info, t_philo *philo_s, int i)
{
    int     y;
    long    x;
    long    n;

    pthread_mutex_lock(&(philo_info->n));
    n = timestamp(philo_info);
    x = n - philo_s[i].last_meal;
    y = philo_s[i].nb_eat;
    pthread_mutex_unlock(&(philo_info->n));
    if (x > philo_info->time_die && philo_s[i].n_eat == 0)
    {
        pthread_mutex_lock(philo_s->msg);
        printf("%lu %d died\n",n, i);
        return (-1);
    }
    if (philo_info->nb_must_eat != -1 && y >= philo_info->nb_must_eat)
        philo_info->nb_philo_eat = philo_info->nb_philo_eat + 1;
    return (0);
}

void    check_died(t_info *philo_info, t_philo *philo_s)
{
    long    i;

    while (1)
    {
        i = 0;
        while (i < philo_info->nb_philo)
        {
            if (check_died_n(philo_info, philo_s, i) == -1)
                return ;
            i++;
        }
        if (philo_info->nb_must_eat != -1)
        {
            if (philo_info->nb_philo_eat == philo_info->nb_philo)
                return ;
            else
                philo_info->nb_philo_eat = 0;
        }
        usleep(10);
    }
}