/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:57:57 by famendes          #+#    #+#             */
/*   Updated: 2024/12/20 14:40:48 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool philo_died(t_philo *philo)
{
	long elapsed;
	long to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(1, philo->data) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	to_die = philo->data->time_to_die / 1000;
	if (elapsed > to_die)
		return (true);
	return (false);
}

void wait_all_threads(t_data *data)
{
	while (!get_bool(&data->data_mutex, &data->all_threads_rdy))
	;
}

void *monitor_dinner(void *monitor)
{
	t_data *data;
	int	i;

	data = (t_data *) monitor;
	while (!all_threads_running(&data->data_mutex, &data->threads_running_nbr, data->philo_nbr))
		;
	while (!simulation_finished(data))
	{
		i = -1;
		while (++i < data->philo_nbr && !simulation_finished(data))
		{
			if (philo_died(&data->philos[i]))
			{
				set_bool(&data->data_mutex, &data->end_simulation, true);
				write_status(DIED, &data->philos[i]);
			}
		}
	}
	return (NULL);
}

bool all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
	bool res;

	res = false;
	pthread_mutex_lock(mutex);
	if (*threads == philo_nbr)
		res = true;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	desyncro_philos(t_philo *philo)
{
	if (philo->data->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(30000, philo->data);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}
