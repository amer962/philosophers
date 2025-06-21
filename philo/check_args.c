/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:58:55 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/12 23:58:55 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_args(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (!is_correct(argv[i]))
        {
            printf("Error args\n");
            return (1);
        }
        i++;
    }
    if (ft_atol(argv[1]) < 1 || ft_atol(argv[2]) <= 0 || ft_atol(argv[3]) <= 0 || ft_atol(argv[4]) <= 0 || (argc == 6 && ft_atol(argv[5]) <= 0))
    {
        printf("Error: Wrong arguments\n");
        return (1);
    }
    return (0);
}