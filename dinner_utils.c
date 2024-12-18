/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:46:23 by famendes          #+#    #+#             */
/*   Updated: 2024/12/17 17:38:57 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void wait_all_threads(t_data *data)
{
	while (!get_bool(&data->data_mutex, &data->all_threads_rdy))
	;
}

long	gettime(int value, t_data *data)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL));
		return (error_and_exit ("Time of day failed", data));
	if (value == 0) //seg
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (value == 1) //miliseg
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (value == 2) //microseg
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		return (error_and_exit ("Wrong input to gettimeofday", data));
	return (0);
}

void	precise_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(2, data);
	while (gettime(2,data) - start < usec)
	{
		if (simulation_finished(data))
			break;
		elapsed = gettime(2, data) - start;
		remaining = usec - elapsed;
		if (remaining > 1000)
			usleep(usec / 2);
		else
		{
			while (gettime(2,data) - start < usec)
				;
		}
	}
}
