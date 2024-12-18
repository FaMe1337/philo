/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:35:36 by famendes          #+#    #+#             */
/*   Updated: 2024/12/18 19:05:20 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo,);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_unlock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo,);
	pthread_mutex_unlock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo,);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(1, philo->data));
	philo->meals_counter++;
	write_status(EATING, philo,);
	precise_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->nbr_of_meals > 0 && philo->meals_counter == philo->data->nbr_of_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_lock(&philo->first_fork->fork);
	pthread_mutex_lock(&philo->second_fork->fork);
}

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
		write_status(SLEEPING, philo);
		precise_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo);
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
			return (error_and_exit("thread join failed", data));
	}
	return (0);
}
