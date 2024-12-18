/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:35:36 by famendes          #+#    #+#             */
/*   Updated: 2024/12/17 17:55:04 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_sim(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(data);
	while (!simulation_finished(philo->data))
	{
		if (philo->full)
			break;
		eat(philo);
		usleep();
		thinking();
	}
	return (NULL);
}

int	dinner_start(t_data *data)
{
	int	i;

	i = 0;
	if ( data->philo_nbr == 1)
		//
	else
	{
		while (i < data->philo_nbr)
		{
			if (pthread_create(&data->philos[i].thread_id, NULL,
				dinner_sim, &data->philos[i]) != 0)
				return (error_and_exit("thread creating failed", data));
		}
		data->start_simulation = gettime(1, data);
		if (data->start_simulation == 1)
			return (error_and_exit("gettimeofday command failed", data));
		set_bool(&data->data_mutex, &data->all_threads_rdy, true);
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philos[i++].thread_id, NULL) != 0)
			return (error_and_exit("thread join failed"));
	}
	return (0);
}

void	write_status()
