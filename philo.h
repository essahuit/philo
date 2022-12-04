/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 08:54:14 by kessalih          #+#    #+#             */
/*   Updated: 2022/07/24 14:20:17 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_info
{
    long            nb_philo;
    long            time_die;
    long            time_eat;
    long            time_sleep;
    long            nb_must_eat;
    long            nb_philo_eat;
    pthread_mutex_t n;
} t_info;

typedef struct s_philo
{
    t_info          *philo_info;
    long          id;
    pthread_mutex_t *forks;
    pthread_mutex_t *msg;
    pthread_t       *threads;
    long            last_meal;
    int             nb_eat;
    int             n_eat;
} t_philo;

void        check_died(t_info *philo_info, t_philo *philo_s);
int         check_died_n(t_info *philo_info, t_philo *philo_s, int i);
void        *routine(void *arg);
void        sleeping(t_philo *philo_s);
void        eating(t_philo *philo_s);
void        thinking(t_philo *philo_s);
int         init_info(int argc, char **argv, t_info *philo_info);
int         check_info(int argc, t_info *philo_info);
int         ft_atoi(const char *str);
int         ft_isdigit(int c);
void        ft_usleep(long x);
long long   timestamp();
void        u_printf(t_philo *philo_s, char *str);
#endif
