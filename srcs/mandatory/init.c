/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:56:04 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/18 18:24:03 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	mutexes_init(t_table *table)
{
	int	i;

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
	int	i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->nb_of_philos);
	while (++i < table->nb_of_philos)
	{
		table->philos[i].id = i;
		table->philos[i].right = &table->forks[i];
		table->philos[i].left = &table->forks[(i + 1) % table->nb_of_philos];
		table->philos[i].table = table;
	}
}

void	thread_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &routine_philo, &table->philos[i]))
			ft_error(table, CREATE);
	}
	i = -1;
	while (++i < table->nb_of_philos)
		if (pthread_join(table->philos[i].thread, NULL))
			ft_error(table, JOIN);
}
