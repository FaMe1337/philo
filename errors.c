/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:20:43 by famendes          #+#    #+#             */
/*   Updated: 2024/12/17 17:03:30 by famendes         ###   ########.fr       */
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
