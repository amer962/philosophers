/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:09:04 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/21 17:09:54 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(void)
{
	struct timeval	time;
	long			milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

void	printf_routine(t_philo *philo, char *m)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	if (!philo->data->died_flag)
	{
		time = time_now() - philo->data->start_time;
		printf("%ld %ld %s\n", time, philo->philo_id, m);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	u_sleep(long time, t_data *data)
{
	int		start;
	int		current;
	long	elapsed;

	start = time_now();
	while (1)
	{
		pthread_mutex_lock(&data->print_lock);
		if (data->died_flag)
		{
			pthread_mutex_unlock(&data->print_lock);
			return ;
		}
		pthread_mutex_unlock(&data->print_lock);
		current = time_now();
		elapsed = current - start;
		if (elapsed >= time)
			break ;
		usleep(1);
	}
}
