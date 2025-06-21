/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:56:46 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/21 16:02:06 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destoy_free(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->numofphilos)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->print_lock);
	free(data->forks);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	philos = NULL;
	if (argc == 5 || argc == 6)
	{
		if (check_args(argc, argv))
			return (1);
		if (init(argv, &data))
			return (ft_return_error("Error in init"));
		if (init_forks(&data))
			return (1);
		if (init_philos(&data, &philos))
			return (1);
		data.philos = philos;
		if (start_sim(&data, philos))
		{
			destoy_free(&data, philos);
			return (1);
		}
	}
	else
		return (ft_return_error("The args ara not correct"));
	destoy_free(&data, philos);
	return (0);
}
