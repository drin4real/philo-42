/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:56:08 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/18 18:16:41 by dbislimi         ###   ########.fr       */
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

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	long		nb_of_meals;
	bool		full;
	long		last_meal_time;

	t_fork 		*left;
	t_fork		*right;
	t_table		*table;
}	t_philo;

struct s_table
{
	long	nb_of_philos;
	long	time_to_eat;
	long	time_to_die;
	long	time_to_sleep;
	long	nbr_limit_meal;
	long	start_time;
	bool	dead;
	t_philo *philos;
	t_fork	*forks;
};

void	ft_exit(char *msg);
void	ft_error(t_table *table, char *msg);

int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);

void	parsing(t_table *table, char **av);
void	mutexes_init(t_table *table);
void	philos_init(t_table *table);
void	thread_init(t_table *table);

void	*routine_philo(void *arg);

#endif