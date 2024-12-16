/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:35:36 by famendes          #+#    #+#             */
/*   Updated: 2024/12/16 18:18:54 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_sim(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;

	wait_all_threads(data);
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
		//começo da sim
		data->start_simulation = gettime(1, data);
		if (data->start_simulation == 1)
			return (1);
		//todas as threads tao on
		set_bool(&data->data_mutex, &data->all_threads_rdy, true);
	}
	return (0);
}
