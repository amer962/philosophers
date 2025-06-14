/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 03:13:41 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/14 03:13:41 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void printf_routine(t_philo *philo, char *m)
{
    long time;

    pthread_mutex_lock(&philo->data->print_lock);
    if (!philo->data->died_flag)
    {
        time = time_now() - philo->data->start_time;
        printf("%ld %ld %s\n", time, philo->philo_id, m);
    }
    pthread_mutex_unlock(&philo->data->print_lock);
}

long time_now(void)
{
    struct timeval time;
    long milliseconds;

    gettimeofday(&time, NULL);
    milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return milliseconds;
}
void ft_take_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_fork->fork);
    pthread_mutex_lock(&philo->right_fork->fork);
    printf_routine(philo, "has taken a fork");
}

void ft_eat(t_philo *philo)
{
    printf_routine(philo, "is eating");
    philo->last_meals = time_now();
    philo->meals++;
    pthread_mutex_unlock(&philo->data->meal_lock);
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);
    pthread_mutex_lock(&philo->data->meal_lock);
}

void ft_sleep(t_philo *philo)
{
    printf_routine(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void ft_think(t_philo *philo)
{
    printf_routine(philo, "is thinking");
}
void *routine(void *philosopher)
{
    t_philo *philo;

    philo = (t_philo *)philosopher;
    while (1)
    {
        if (philo->data->died_flag)
            break;
        ft_take_forks(philo);
        ft_eat(philo);
        ft_sleep(philo);
        ft_think(philo);
        if (philo->data->numofmeals != -1 && philo->meals == philo->data->numofmeals)
            break;
    }
    return (NULL);
}

int start_sim(t_data *data, t_philo *philos)
{
    int i;

    data->start_time = time_now();
    i = 0;
    while (i < data->numofphilos)
    {
        philos[i].last_meals = data->start_time;
        if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
            return (ft_return_error("Failed to create thread"));
        usleep(100);
        i++;
    }
    i = 0;
    while (i < data->numofphilos)
        pthread_join(philos[i++].thread, NULL);
    return (0);
}
