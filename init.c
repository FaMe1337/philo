/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:22:19 by famendes          #+#    #+#             */
/*   Updated: 2024/12/18 18:44:19 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	philo->first_fork = &forks[(i + 1) % philo_nbr];
	philo->second_fork = &forks[i];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % philo_nbr];
	}
}

static int philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].full = false;
		data->philos[i].meals_counter = 0;
		data->philos[i].data = data;
		if ((pthread_mutex_init(&data->philos[i].philo_mutex, NULL)) != 0);
			return (error_and_exit("Mutex init for philo mutex failed", data));
		assign_forks(&data->philos[i], data->forks, i);
		i++;
	}
	return (0);
}

int	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->end_simulation = false;
	data->all_threads_rdy = false;
	if (data->philo_nbr >= 200)
		return (error_and_exit("Lets try to not burn the PC", 0));
	if (!(data->philos = malloc(sizeof(t_philo) * data->philo_nbr)))
		return (error_and_exit("Malloc for philos struc failed", 0));
	if (!(data->forks = malloc(sizeof(t_fork) * data->philo_nbr)))
		return (error_and_exit("Malloc for forks struc failed", data));
	if ((pthread_mutex_init(&data->data_mutex, NULL)) != 0);
		return (error_and_exit("Mutex init for data_mutex failed", data));
	if ((pthread_mutex_init(&data->mutex_write, NULL)) != 0);
		return (error_and_exit("Mutex init for write mutex failed", data));
	while (i < data->philo_nbr)
	{
		if ((pthread_mutex_init(&data->forks[i].fork, NULL)) != 0)
			return (error_and_exit("Mutex init for fork failed", data));
		data->forks[i].fork_id = i;
		i++;
	}
	if (philo_init(data))
		return (1);
	return (0);
}
