#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_info
{
    long    nb_philo;
    long    time_die;
    long    time_eat;
    long    time_sleep;
    long    nb_must_eat;
} t_info;

typedef struct s_philo
{
    t_info          *philo_info;
    size_t          id;
    pthread_mutex_t *forks;
    pthread_mutex_t *msg;
    pthread_t       *threads;
} t_philo;


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t				i;
	size_t              k;
    unsigned long long	n;

	i = 0;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
    k = i;
    while(str[k])
    {
        if (ft_isdigit(str[k]) == 0)
            return (-1);
        k++;
    }
	while (str[i] >= '0' && str[i] <= '9')
		n = n * 10 + (str[i++] - '0');
	return ((int)n);
}

int check_info(int argc, t_info *philo_info)
{
    if (philo_info->nb_philo <= 0 || philo_info->time_die <= 0 || philo_info->time_eat <= 0 || philo_info->time_sleep <= 0)
        return (-1);
    if (argc == 6 && philo_info->nb_must_eat <= 0)
        return (-1);
    return (1);
}

int init_info(int argc, char **argv, t_info *philo_info)
{
    philo_info->nb_philo = ft_atoi(argv[1]);
    philo_info->time_die = ft_atoi(argv[2]);
    philo_info->time_eat = ft_atoi(argv[3]);
    philo_info->time_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        philo_info->nb_must_eat = ft_atoi(argv[5]);
    else
        philo_info->nb_must_eat = -1;
    return (check_info(argc, philo_info));
}

pthread_mutex_t *create_forks(t_info *philo_info)
{
    pthread_mutex_t *forks;
    int             i;

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
    int             i;

    philo_s = malloc(sizeof(t_philo) * philo_info->nb_philo);
    threads = malloc(sizeof(pthread_t) * philo_info->nb_philo);
    i = 0;
    pthread_mutex_init(&msg, NULL);
    while (i < philo_info->nb_philo)
    {
        philo_s[i].id = i;
        philo_s[i].forks = forks;
        philo_s[i].msg = &msg;
        philo_s[i].threads = threads;
        philo_s[i].philo_info = philo_info;
        i++;
    }
    return (philo_s);
}

void    thinking(t_philo *philo_s)
{
    pthread_mutex_lock(philo_s->msg);
    printf("thinking  %zu\n",philo_s->id);
    pthread_mutex_unlock(philo_s->msg);
}

void    eating(t_philo *philo_s)
{
    pthread_mutex_lock(&philo_s->forks[philo_s->id]);
    printf("take fork %zu\n",philo_s->id);
    if (philo_s->id + 1 == philo_s->philo_info->nb_philo)
        pthread_mutex_lock(&philo_s->forks[0]);
    else
        pthread_mutex_lock(&philo_s->forks[philo_s->id + 1]);
    printf("take fork 2 %zu\n",philo_s->id);
    printf("eating  %zu\n",philo_s->id);
    usleep(2000);
    pthread_mutex_unlock(&philo_s->forks[philo_s->id]);
    if (philo_s->id + 1 == philo_s->philo_info->nb_philo)
        pthread_mutex_unlock(&philo_s->forks[0]);
    else
        pthread_mutex_unlock(&philo_s->forks[philo_s->id + 1]);
}

void    sleeping(t_philo *philo_s)
{
    pthread_mutex_lock(philo_s->msg);
    printf("sleeping %zu \n",philo_s->id);
    usleep(2000);
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

void    create_threads(t_info *philo_info, t_philo *philo_s)
{
    int i;

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
    int     i;

    i = 0;
    philo_info = malloc(sizeof(t_info));
    if (argc < 5 || argc > 6 || init_info(argc ,argv, philo_info) == -1)
    {
        free(philo_info);
        printf("error 1\n");
        return (1);
    }
    forks = create_forks(philo_info);
    philo_s = create_philos(philo_info, forks);
    create_threads(philo_info, philo_s);
    while (i < philo_info->nb_philo)
    {
        pthread_join(philo_s[i].threads[i],NULL);
        i++;
    }   
}