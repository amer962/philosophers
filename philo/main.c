/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:56:46 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/12 23:56:46 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;
    t_philo *philos;
    
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
        if (start_sim(&data, philos))
            return (1);
    }
    else
        return (ft_return_error("The args ara not correct"));
    return (0);
}