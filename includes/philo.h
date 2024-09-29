/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:56:08 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/29 17:25:50 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define G "\033[32m"
# define R "\033[1;31m"
# define r "\033[31m"
# define RST "\033[0m"
# define NEGATIVE "Error: unvalid inputs\n"RST r"(negative number)"RST
# define INTMAX "Error: unvalid inputs\n"RST r"(INT_MAX)"RST
# define INPUT "Error: wrong input.\n"RST G"Correct is ./philo 5 800 200 200"RST
# define CREATE "Error: failed to create a thread.\n"RST
# define JOIN "Error: failed to join a thread.\n"RST

typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	size_t		start;
	size_t		nb_of_meals;
	bool		full;
	size_t		last_meal_time;

	t_mtx 		*left;
	t_mtx		*right;
	t_table		*table;
}	t_philo;

struct s_table
{
	size_t	nb_of_philos;
	size_t	time_to_eat;
	size_t	time_to_die;
	size_t	time_to_sleep;
	size_t	nbr_limit_meal;
	size_t	start_time;
	bool	all_threads_ready;
	bool	dead;

	pthread_t	checker;
	t_mtx	ready;
	t_mtx	*check_meals;
	t_mtx	check_dead;
	t_philo *philos;
	t_mtx	*forks;
};

void	ft_exit(char *msg);
void	ft_error(t_table *table, char *msg);

int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);

void	parsing(t_table *table, char **av);
void	mutexes_init(t_table *table);
void	destroy_mutexes(t_table *table);
void	philos_init(t_table *table);
void	thread_init(t_table *table);

void	*routine_philo(void *arg);
void	*routine_checker(void *arg);

#endif