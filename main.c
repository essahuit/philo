#include "philo.h"

pthread_mutex_t *create_forks(t_info *philo_info)
{
    pthread_mutex_t *forks;
    long            i;

    i = 0;
    forks = malloc(sizeof(pthread_mutex_t) * philo_info->nb_philo);
    while (i < philo_info->nb_philo)
    {
        pthread_mutex_init(forks + i, NULL);
        i++;
    }
    return (forks);
}

t_philo *create_philos(t_info *philo_info, pthread_mutex_t *forks)
{
    t_philo         *philo_s;
    pthread_mutex_t msg;
    pthread_t       *threads;
    long            i;

    philo_s = malloc(sizeof(t_philo) * philo_info->nb_philo);
    threads = malloc(sizeof(pthread_t) * philo_info->nb_philo);
    i = 0;
    pthread_mutex_init(&msg, NULL);
    while (i < philo_info->nb_philo)
    {
        philo_s[i].id = i;
        philo_s[i].nb_eat = 0;
        philo_s[i].forks = forks;
        philo_s[i].msg = &msg;
        philo_s[i].threads = threads;
        philo_s[i].philo_info = philo_info;
        philo_s[i].last_meal = timestamp();
        philo_s[i].n_eat = 0;
        i++;
    }
    return (philo_s);
}

void    create_threads(t_info *philo_info, t_philo *philo_s)
{
    long    i;

    i = 0;
    while (i < philo_info->nb_philo)
    {
        if (pthread_create(&philo_s[i].threads[i],NULL, &routine, &philo_s[i]) != 0)
        {
            printf("pthread create error\n");
            return ;
        }
        usleep(100);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_info  *philo_info;
    pthread_mutex_t *forks;
    t_philo *philo_s;

    philo_info = malloc(sizeof(t_info));
    if (argc < 5 || argc > 6 || init_info(argc ,argv, philo_info) == -1)
    {
        free(philo_info);
        printf("parsing error\n");
        return (1);
    }
    forks = create_forks(philo_info);
    philo_s = create_philos(philo_info, forks);
    create_threads(philo_info, philo_s);
    check_died(philo_info, philo_s);
}