#include "philo.h"

void    u_printf(t_philo *philo_s, char *str)
{
    pthread_mutex_lock(philo_s->msg);
    printf("%lld %zu %s",timestamp(),philo_s->id,str);
    pthread_mutex_unlock(philo_s->msg);
}

void    thinking(t_philo *philo_s)
{
    pthread_mutex_lock(philo_s->msg);
    printf("%lld %zu is thinking\n",timestamp(),philo_s->id);
    pthread_mutex_unlock(philo_s->msg);
}

void    eating(t_philo *philo_s)
{
    pthread_mutex_lock(&philo_s->forks[philo_s->id]);
    u_printf(philo_s, "has taken a fork\n");
    if (philo_s->id + 1 == philo_s->philo_info->nb_philo)
        pthread_mutex_lock(&philo_s->forks[0]);
    else
        pthread_mutex_lock(&philo_s->forks[philo_s->id + 1]);
    u_printf(philo_s, "has taken a fork\n");
    u_printf(philo_s, "is eating\n");
    philo_s->n_eat = 1;
    pthread_mutex_lock(&(philo_s->philo_info->n));
    philo_s->nb_eat = philo_s->nb_eat + 1;
    philo_s->last_meal = timestamp();
    pthread_mutex_unlock(&(philo_s->philo_info->n));
    ft_usleep(philo_s->philo_info->time_eat);
    philo_s->n_eat = 0;
    pthread_mutex_unlock(&philo_s->forks[philo_s->id]);
    if (philo_s->id + 1 == philo_s->philo_info->nb_philo)
        pthread_mutex_unlock(&philo_s->forks[0]);
    else
        pthread_mutex_unlock(&philo_s->forks[philo_s->id + 1]);
}

void    sleeping(t_philo *philo_s)
{
    pthread_mutex_lock(philo_s->msg);
    printf("%lld %zu is sleeping\n",timestamp(),philo_s->id);
    ft_usleep(philo_s->philo_info->time_sleep);
    pthread_mutex_unlock(philo_s->msg);
}

void    *routine(void *arg)
{
    t_philo *philo_s;

    philo_s = (t_philo *)arg;
    while (1)
    {
        eating(philo_s);
        sleeping(philo_s);
        thinking(philo_s);
    }
    return (NULL);
}