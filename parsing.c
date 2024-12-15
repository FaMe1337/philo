/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:45:06 by famendes          #+#    #+#             */
/*   Updated: 2024/12/15 18:03:17 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static long	ft_atol(const char *nptr)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
		error_and_exit("Give only positive numbers");
	else if (*nptr == '+')
		nptr++;
	if (!is_digit(*nptr))
		error_and_exit("Input must be all numbers");
	while (*nptr >= '0' && *nptr <= '9' && result <= INT_MAX)
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	if (result > INT_MAX)
		error_and_exit("Number used is too big");
	return (result);
}

void	parse_input(t_data *data, char **av, int ac)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (!av[i++][0])
			error_and_exit("Please use valid arguments");
	}
	data->philo_nbr = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]) *1000;
	data->time_to_eat= ft_atol(av[3]) *1000;
	data->time_to_sleep = ft_atol(av[4]) *1000;
	if (data->time_to_die < 60000
		|| data->time_to_eat < 60000
		|| data->time_to_sleep < 60000)
		{
			error_and_exit("Use timestamps bigger than 60ms pls");
			return;
		}
	if (av[5])
		data->nbr_of_meals = ft_atol(av[5]);
	else
	data->nbr_of_meals = -1;
}
