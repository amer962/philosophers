/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:29:31 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/21 16:23:44 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_return_error(char *m)
{
	write(2, m, ft_strlen(m));
	write(2, "\n", 1);
	return (1);
}

long	ft_atol(const char *nptr)
{
	int					i;
	int					sn;
	unsigned long long	num;
	char				*a;

	a = (char *)nptr;
	i = 0;
	sn = 1;
	num = 0;
	while ((a[i] == ' ') || (a[i] >= 9 && a[i] <= 13))
		i++;
	if (a[i] == '-' || a[i] == '+')
	{
		if (a[i] == '-')
			sn = sn * -1;
		i++;
	}
	while (a[i] <= '9' && a[i] >= '0')
	{
		num = num * 10 + (a[i] - '0');
		i++;
	}
	return (sn * num);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}

int	is_correct(char *av)
{
	int	j;

	j = 0;
	while (av[j] == ' ' || av[j] == '\t' || av[j] == '\n' || av[j] == '\v'
		|| av[j] == '\f' || av[j] == '\r')
		j++;
	while (av[j] == '+')
		j++;
	if (av[j] == '-')
		return (0);
	if (!ft_isdigit(av[j]))
		return (0);
	while (ft_isdigit(av[j]))
		j++;
	if (av[j] != '\0')
		return (0);
	return (1);
}
