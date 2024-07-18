#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			eating;
	int			meals_eaten;
	size_t		last_meal;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		start_time;
	int			num_of_philos;
	int			num_times_to_eat;
	int			*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fort;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef	struct	s_program
{
	int			dead_flag;
	int			num_of_philos;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_program;

size_t	ft_atoul(const char *nb);
int	philos_init(char **av, t_program *pro);
void	*philo_routine(void *arg);
int		check_arguments(int ac, char** av, t_program *pro);
void	mutexes_init(t_program *pro);
int	ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
void	eat(t_philo *philo);

#endif