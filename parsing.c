/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:45:06 by famendes          #+#    #+#             */
/*   Updated: 2024/12/16 17:34:56 by famendes         ###   ########.fr       */
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
		return (error_and_exit("Give only positive numbers", 0));
	else if (*nptr == '+')
		nptr++;
	if (!is_digit(*nptr))
		return (error_and_exit("Input must be all numbers", 0));
	while (*nptr >= '0' && *nptr <= '9' && result <= INT_MAX)
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	if (result > INT_MAX)
		return (error_and_exit("Number used is too big", 0));
	return (result);
}

int	parse_input(t_data *data, char **av, int ac)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (!av[i++][0])
			return (error_and_exit("Please use valid arguments", 0));
	}
	data->philo_nbr = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]) *1000;
	data->time_to_eat= ft_atol(av[3]) *1000;
	data->time_to_sleep = ft_atol(av[4]) *1000;
	 if (data->philo_nbr <= 0)
        return (error_and_exit("Number of philosophers must be greater than 0", 0));
	if (data->time_to_die < 60000
		|| data->time_to_eat < 60000
		|| data->time_to_sleep < 60000)
			return (error_and_exit("Use timestamps bigger than 60ms pls", 0));
	if (av[5])
		data->nbr_of_meals = ft_atol(av[5]);
			if (data->nbr_of_meals <= 0)
				return (error_and_exit("Please give positive number or non-zero for meals", 0));
	else
	data->nbr_of_meals = -1;
	return (0);
}
