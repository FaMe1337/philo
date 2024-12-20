/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_clean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:20:43 by famendes          #+#    #+#             */
/*   Updated: 2024/12/19 19:26:37 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	return;
}

int	error_and_exit(char *error, t_data *data)
{
	if (data != 0)
		free_data(data);
	printf("%s\n", error);
	return (1);
}

void	clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		pthread_mutex_destroy(&data->philos[i++].philo_mutex);
	}
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->mutex_write);
	free(data->forks);
	free(data->philos);
}
