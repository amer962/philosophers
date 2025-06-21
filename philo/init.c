/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:31:43 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/21 14:00:24 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init(char **argv, t_data *data)
{
    data->numofphilos = ft_atol(argv[1]);
    data->time_to_die = ft_atol(argv[2]);
    data->time_to_eat = ft_atol(argv[3]);
    data->time_to_sleep = ft_atol(argv[4]);
    if (argv[5])
        data->numofmeals = ft_atol(argv[5]);
    else
        data->numofmeals = -1;
    data->died_flag = false;
    data->start_time = 0;
    data->forks = NULL;
    if ((pthread_mutex_init(&data->print_lock, NULL)) || (pthread_mutex_init(&data->meal_lock, NULL)) != 0)
        return (1);
    return (0);
}

int init_forks(t_data *data)
{
    int i = 0;

    data->forks = malloc(sizeof(t_fork) * data->numofphilos);
    if(!data->forks)
        return (ft_return_error("failed to allocate malloc for forks"));
    while (i < data->numofphilos)
    {
        data->forks[i].id = i + 1;
        if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
            return (ft_return_error("Faild mutex"));
        i++;
    }
    return (0);
}

int init_philos(t_data *data, t_philo **philos)
{
    int i;

    *philos = malloc(sizeof(t_philo) * data->numofphilos);
    if (!*philos)
        return(ft_return_error("failed malloc"));
    i = 0;
    while (i < data->numofphilos)
    {
        (*philos)[i].philo_id = i + 1;
        (*philos)[i].meals = 0;
        (*philos)[i].last_meals = 0;
        (*philos)[i].left_fork = &data->forks[i];
        (*philos)[i].right_fork = &data->forks[(i + 1) % data->numofphilos];
        (*philos)[i].data = data;
        i++;
    }
    return (0);
}
