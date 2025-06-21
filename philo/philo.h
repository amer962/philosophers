/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:07:53 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/21 12:32:51 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data		t_data;

typedef struct s_fork
{
    int id;
    pthread_mutex_t fork;
}  t_fork;

typedef struct s_philo
{
    long        philo_id;
    int         meals;
    long        last_meals;
    t_fork      *left_fork;
    t_fork      *right_fork;
    t_data      *data;
    pthread_t   thread;
}   t_philo;

typedef struct s_data
{
    long numofphilos;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long numofmeals;
    bool died_flag;
    long start_time;
    pthread_mutex_t meal_lock;
    pthread_mutex_t print_lock;
    t_fork *forks;
    t_philo *philos;
}   t_data;

int     init(char **argv, t_data *data);
int	    ft_return_error(char *m);
int     check_args(int argc, char **argv);
long    ft_atol(const char *nptr);
int	    ft_isdigit(int c);
int     is_correct(char *av);
int     init_forks(t_data *data);
int     init_philos(t_data *data, t_philo **philos);
long    time_now(void);
void    printf_routine(t_philo *philo, char *m);
int     start_sim(t_data *data, t_philo *philos);

#endif