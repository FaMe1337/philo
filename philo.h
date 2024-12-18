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
	long	meals_counter;
	long	last_meal_time;  // tempo desde a ultima refeiçao
	bool	full;
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
	bool	all_threads_rdy;
	pthread_mutex_t	data_mutex; //semaforo da mesa
	pthread_mutex_t	mutex_write;
	t_fork *forks; //array de forks
	t_philo *philos; // array de philos
};

// error
int	error_and_exit(char *error, t_data *data);

// parsing and data init
int	parse_input(t_data *data, char **av, int ac);
int	data_init(t_data *data);

//controls
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t * mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t * mutex, long *value);
bool	simulation_finished(t_data * data);

//dinner
int		dinner_start(t_data *data);
void	*dinner_sim(void *data);

//utils
void 	wait_all_threads(t_data *data);
long	gettime(int value, t_data *data);
void	precise_usleep(long usec, t_data *data);

#endif
