/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:56:04 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/21 19:14:45 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	mutexes_init(t_table *table)
{
	size_t	i;

	i = -1;
	table->forks = malloc(sizeof(t_fork) * table->nb_of_philos);
	while (++i < table->nb_of_philos)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
	}
}

void	philos_init(t_table *table)
{
	size_t	i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->nb_of_philos);
	while (++i < table->nb_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].full = false;
		table->philos[i].right = &table->forks[i];
		table->philos[i].left = &table->forks[(i + 1) % table->nb_of_philos];
		table->philos[i].table = table;
	}
}

void	thread_init(t_table *table)
{
	size_t	i;

	i = -1;
	if (table->nbr_limit_meal == 0)
		return (0);
	table->dead = 0;
	table->all_threads_ready = false;
	while (++i < table->nb_of_philos)
	{
		table->philos[i].last_meal_time = 0;
		table->philos[i].nb_of_meals = 0;
		if (pthread_create(&table->philos[i].thread, NULL, &routine_philo, &table->philos[i]))
			ft_error(table, CREATE);
	}
	table->start_time = get_current_time();
	table->all_threads_ready = true;
}
