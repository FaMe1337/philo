/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:35:36 by famendes          #+#    #+#             */
/*   Updated: 2025/01/07 18:32:27 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(1, philo->data));
	philo->meals_counter++;
	write_status(EATING, philo);
	precise_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->nbr_of_meals > 0 && philo->meals_counter == philo->data->nbr_of_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}
void	thinking(t_philo *philo,  bool value)
{
	long t_eat;
	long t_sleep;
	long t_think;

	if (!value)
	write_status(THINKING, philo);
	//se for n par nao queremos saber de um sistema justo
	if (philo->data->philo_nbr % 2 == 0)
		return;
	t_eat = philo->data->time_to_eat;
	t_sleep = philo->data->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->data);
}

void	*solo_philo(void *data)
{
	t_philo *philo;

	philo = (t_philo *) data;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(1, data));
	increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->data))
		usleep(200);
	return (NULL);
}

int	multiple_philo(t_data *data)
{	int	i;

	i = 0;
	while (i < data->philo_nbr)
		{
			if (pthread_create(&data->philos[i].thread_id, NULL,
				dinner_sim, &data->philos[i]))
				return (error_and_exit("thread creating for multiple philo failed", data));
			i++;
		}
	return (0);
}

int	dinner_start(t_data *data)
{
	int	i;

	i = 0;
	if ( data->philo_nbr == 1)
	{
		if (pthread_create(&data->philos[0].thread_id, NULL,
			solo_philo, &data->philos[0]))
			return (error_and_exit("thread creating for solo philo failed", data));
	}
	else
	{
		if (multiple_philo(data))
			return (1);
	}
	if (pthread_create(&data->monitor, NULL, monitor_dinner, data))
		return (error_and_exit("thread creating for monitor failed", data));
	data->start_simulation = gettime(1, data);
	set_bool(&data->data_mutex, &data->all_threads_rdy, true);
	while (i < data->philo_nbr && !data->end_simulation)
	{
		if (pthread_join(data->philos[i++].thread_id, NULL) != 0)
			return (error_and_exit("thread join failed", data));
	}
	set_bool(&data->data_mutex, &data->end_simulation, true);
	if (pthread_join(data->monitor, NULL) != 0)
		return (error_and_exit("thread join failed", data));
	return (0);
}
