/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:17:42 by famendes          #+#    #+#             */
/*   Updated: 2024/12/15 17:59:49 by famendes         ###   ########.fr       */
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
		parse_input(&data, av, ac);
		//data_init(&data);
		//simulation_start(&data);
		// maybe clean
	}
	else
		error_and_exit("Wrong number of arguments");
	return (0);
}
