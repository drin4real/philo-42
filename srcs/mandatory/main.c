/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:55:44 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/25 15:09:30 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	main(int ac, char **av)
{
	t_table table;
	size_t		i;
	
	i = -1;
	if (ac < 5 || ac > 6)
		ft_exit(INPUT);
	parsing(&table, av);
// printf("philo : %ld\ndie : %ld\neat : %ld\nsleep : %ld\nnb_of_meal : %ld\n", table.nb_of_philos, table.time_to_die, table.time_to_eat, table.time_to_sleep, table.nbr_limit_meal);
	mutexes_init(&table);
	philos_init(&table);
	thread_init(&table);
	pthread_join(table.checker, NULL);
	while (++i < table.nb_of_philos)
		if (pthread_join(table.philos[i].thread, NULL))
			ft_error(&table, JOIN);
	destroy_mutexes(&table);
}