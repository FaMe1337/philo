#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data	t_data;


typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}				t_fork;


typedef struct s_philo
{
	int		id;
	int		meals_counter;
	bool	full;
	long	last_meal_time;  // tempo desde a ultima refeiçao
	t_fork	*first_fork;
	t_fork	*second_fork;
	pthread_t	thread_id;  // cada philo é uma thread
	t_data		*data;
}			t_philo;

struct s_data
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_of_meals;
	long	start_simulation;
	bool	end_simulation; // quando alguem morre ou estao todos cheios
	t_fork *forks; //array de forks
	t_philo *philos; // array de philos
};

// error
void	error_and_exit(char *error);

// parsing
void	parse_input(t_data *data, char **av, int ac);

//data init
void	data_init(t_data *data);

#endif
