/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:11:49 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/21 16:38:25 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		printf_routine(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork);
		printf_routine(philo, "has taken a fork");
		usleep(100);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		printf_routine(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->fork);
		printf_routine(philo, "has taken a fork");
	}
}

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meals = time_now();
	philo->meals++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	printf_routine(philo, "is eating");
	u_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

static void	ft_sleep(t_philo *philo)
{
	printf_routine(philo, "is sleeping");
	u_sleep(philo->data->time_to_sleep, philo->data);
}

static void	ft_think(t_philo *philo)
{
	printf_routine(philo, "is thinking");
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (1)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		if (philo->data->died_flag)
		{
			pthread_mutex_unlock(&philo->data->print_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->print_lock);
		ft_take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		if (philo->data->numofmeals != -1
			&& philo->meals == philo->data->numofmeals)
			break ;
	}
	return (NULL);
}
