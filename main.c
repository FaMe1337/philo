/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:17:42 by famendes          #+#    #+#             */
/*   Updated: 2024/12/20 14:30:50 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 5 200 200 200 [5]
// tenho de arranjar um metodo facil de sair quando tenho um erro

int	main(int ac, char **av)
{
	t_data data;

	if (ac == 5 || ac == 6)
	{
		if (parse_input(&data, av))
			return (1);
		if (data_init(&data))
			return (1);
		if (dinner_start(&data))
			return (1);
		clean(&data);
	}
	else
		return (error_and_exit("Wrong number of arguments", 0));
	return (0);
}
