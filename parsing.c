#include "philo.h"

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
    philo_info->nb_philo_eat = 0;
    pthread_mutex_init(&(philo_info->n), NULL);
    if (argc == 6)
        philo_info->nb_must_eat = ft_atoi(argv[5]);
    else
        philo_info->nb_must_eat = -1;
    return (check_info(argc, philo_info));
}