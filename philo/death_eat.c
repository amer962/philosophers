/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:04:23 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/21 17:10:18 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, int i)
{
	long	last_meal;
	int		meals;

	pthread_mutex_lock(&data->meal_lock);
	last_meal = data->philos[i].last_meals;
	meals = data->philos[i].meals;
	pthread_mutex_unlock(&data->meal_lock);
	if ((time_now() - last_meal) >= data->time_to_die)
	{
		pthread_mutex_lock(&data->print_lock);
		if (!data->died_flag)
		{
			data->died_flag = true;
			printf("%ld %ld died\n", time_now() - data->start_time,
				data->philos[i].philo_id);
		}
		pthread_mutex_unlock(&data->print_lock);
		return (1);
	}
	return (data->numofmeals != -1 && meals >= data->numofmeals);
}

static int	check_all_ate(t_data *data, int all_ate)
{
	if (data->numofmeals != -1 && all_ate == data->numofphilos)
	{
		pthread_mutex_lock(&data->print_lock);
		data->died_flag = true;
		pthread_mutex_unlock(&data->print_lock);
		return (1);
	}
	return (0);
}

void	*death_eat_monitor(void *x)
{
	t_data	*data;
	int		i;
	int		all_ate;

	data = (t_data *)x;
	while (1)
	{
		i = -1;
		all_ate = 0;
		while (++i < data->numofphilos)
		{
			if (check_death(data, i))
			{
				if (data->died_flag)
					return (NULL);
				else
					all_ate++;
			}
		}
		if (check_all_ate(data, all_ate))
			return (NULL);
		usleep(100);
	}
}
