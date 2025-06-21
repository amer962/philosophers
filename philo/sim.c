/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 03:13:41 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/21 18:30:37 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->numofphilos)
	{
		philos[i].last_meals = data->start_time;
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (ft_return_error("Failed to create thread"));
		usleep(430);
		i++;
	}
	return (0);
}

static int	join_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->numofphilos)
	{
		if (pthread_join(philos[i++].thread, NULL) != 0)
			return (ft_return_error("Failed to join thread"));
	}
	return (0);
}

int	start_sim(t_data *data, t_philo *philos)
{
	pthread_t	monitor;

	data->start_time = time_now();
	if (data->numofphilos == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(data->time_to_die * 1000);
		printf("%ld 1 died\n", data->time_to_die);
		return (0);
	}
	if (start_threads(data, philos) != 0)
		return (1);
	if (pthread_create(&monitor, NULL, &death_eat_monitor, data) != 0)
		return (ft_return_error("Failed to create thread"));
	if (join_threads(data, philos) != 0)
		return (1);
	if (pthread_join(monitor, NULL) != 0)
		return (ft_return_error("Failed to join thread"));
	return (0);
}

// #include "philo.h"

// static int	check_philo_death(t_data *data, int i)
// {
// 	long	last_meal;
// 	int		meals;

// 	pthread_mutex_lock(&data->meal_lock);
// 	last_meal = data->philos[i].last_meals;
// 	meals = data->philos[i].meals;
// 	pthread_mutex_unlock(&data->meal_lock);
// 	if ((time_now() - last_meal) >= data->time_to_die)
// 	{
// 		pthread_mutex_lock(&data->print_lock);
// 		if (!data->died_flag)
// 		{
// 			data->died_flag = true;
// 			printf("%ld %ld died\n", time_now() - data->start_time,
// 				data->philos[i].philo_id);
// 		}
// 		pthread_mutex_unlock(&data->print_lock);
// 		return (1);
// 	}
// 	return (data->numofmeals != -1 && meals >= data->numofmeals);
// }

// void	*death_eat_monitor(void *x)
// {
// 	t_data	*data;
// 	int		i;
// 	int		all_ate;

// 	data = (t_data *)x;
// 	while (1)
// 	{
// 		i = -1;
// 		all_ate = 0;
// 		while (++i < data->numofphilos)
// 		{
// 			if (check_philo_death(data, i))
// 				return (NULL);
// 			if (data->numofmeals != -1
// 				&& data->philos[i].meals >= data->numofmeals)
// 				all_ate++;
// 		}
// 		if (check_all_ate(data, all_ate))
// 			return (NULL);
// 		usleep(100);
// 	}
// }

// static int	start_threads(t_data *data, t_philo *philos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->numofphilos)
// 	{
// 		philos[i].last_meals = data->start_time;
// 		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
// 			return (ft_return_error("Failed to create thread"));
// 		usleep(100);
// 		i++;
// 	}
// 	return (0);
// }

// static int	join_threads(t_data *data, t_philo *philos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->numofphilos)
// 	{
// 		if (pthread_join(philos[i++].thread, NULL) != 0)
// 			return (ft_return_error("Failed to join thread"));
// 	}
// 	return (0);
// }

// int	start_sim(t_data *data, t_philo *philos)
// {
// 	pthread_t	monitor;

// 	data->start_time = time_now();
// 	if (data->numofphilos == 1)
// 	{
// 		printf("0 1 has taken a fork\n");
// 		usleep(data->time_to_die * 1000);
// 		printf("%ld 1 died\n", data->time_to_die);
// 		return (0);
// 	}
// 	if (start_threads(data, philos) != 0)
// 		return (1);
// 	if (pthread_create(&monitor, NULL, &death_eat_monitor, data) != 0)
// 		return (ft_return_error("Failed to create thread"));
// 	if (join_threads(data, philos) != 0)
// 		return (1);
// 	if (pthread_join(monitor, NULL) != 0)
// 		return (ft_return_error("Failed to join thread"));
// 	return (0);
// }
