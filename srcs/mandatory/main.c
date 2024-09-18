/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:55:44 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/18 17:56:25 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	main(int ac, char **av)
{
	t_table table;
	
	if (ac < 5 || ac > 6)
		ft_exit(INPUT);
	parsing(&table, av);
// printf("philo : %ld\ndie : %ld\neat : %ld\nsleep : %ld\nnb_of_meal : %ld\n", table.nb_of_philos, table.time_to_die, table.time_to_eat, table.time_to_sleep, table.nbr_limit_meal);
	mutexes_init(&table);
	philos_init(&table);
	thread_init(&table);
}