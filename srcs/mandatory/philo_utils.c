/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:46:37 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/18 18:21:15 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

void	ft_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

size_t	ft_atoul(const char *nb)
{
	size_t	res;
	int	sign;
	
	res = 0;
	sign = 1;
	while ((*nb >= 9 && *nb <= 13) || *nb == ' ')
		++nb;
	while (*nb == '-' || *nb == '+')
		if (*nb++ == '-')
			sign *= -1;
	while (*nb >= '0' && *nb <= '9')
		res = res * 10 + (*nb++ - '0');
	if (sign == -1)
		return (0);
	return (res * sign);
}

int	check_arguments(int ac, char** av, t_program *pro)
{
	if (ac < 5)
		ft_exit("Error: Missing arguments\n");
	else if (ac > 6)
		ft_exit("Error: Too many arguments\n");
	else
	{
		pro->num_of_philos = (int)ft_atoul(av[1]);
		if (pro->num_of_philos < 1)
			ft_exit("Not enough philos\n");
	}
	return (1);
}

static int	philos_init_bis(t_program *pro)
{
	int	i;

	i = pro->num_of_philos;
	while (i--)
	{
		pro->philos[i].r_fork = &pro->forks[i % pro->num_of_philos];
		pro->philos[i].l_fort = &pro->forks[(i + 1) % pro->num_of_philos];
		pro->philos[i].dead_lock = &pro->dead_lock;
		pro->philos[i].meal_lock = &pro->meal_lock;
		pro->philos[i].write_lock = &pro->write_lock;
	}
	while (++i < pro->num_of_philos)
		if (pthread_create(&pro->philos[i].thread, NULL, &philo_routine, &pro->philos[i]) != 0)
			return (0);
	return (1);
}

int	philos_init(char **av, t_program *pro)
{
	size_t	die_eat_sleep[3];
	int		i;

	i = 3;
	pro->dead_flag = 0;
	pro->philos = malloc(sizeof(t_philo) * (pro->num_of_philos));
	while (i--)
	{
		die_eat_sleep[i] = ft_atoul(av[2 + i]);
		if (!(die_eat_sleep[i]))
			return (0);
	}
	while (++i < pro->num_of_philos)
	{
		pro->philos[i].id = i + 1;
		pro->philos[i].eating = 0;
		pro->philos[i].meals_eaten = 0;
		pro->philos[i].dead = &pro->dead_flag;
		pro->philos[i].num_of_philos = pro->num_of_philos;
		pro->philos[i].time_to_die = die_eat_sleep[0];
		pro->philos[i].time_to_eat = die_eat_sleep[1];
		pro->philos[i].time_to_sleep = die_eat_sleep[2];
	}
	return (philos_init_bis(pro));
}

void	mutexes_init(t_program *pro)
{
	int	i;
	
	i = -1;
	pro->forks = malloc(sizeof(pthread_mutex_t) * pro->num_of_philos);
	while (++i < pro->num_of_philos)
		pthread_mutex_init(&pro->forks[i], NULL);
	pthread_mutex_init(&pro->dead_lock, NULL);
	pthread_mutex_init(&pro->meal_lock, NULL);
	pthread_mutex_init(&pro->write_lock, NULL);
	// while (++i < pro->philos[0].num_of_philos)
	// {
	// 	pro->philos[i].dead_lock = &pro->dead_lock;
	// 	pro->philos[i].meal_lock = &pro->meal_lock;
	// 	pro->philos[i].write_lock = &pro->write_lock;
	// }
}