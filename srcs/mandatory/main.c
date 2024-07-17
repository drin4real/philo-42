/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:12:58 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/17 18:15:27 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*monitor(void *arg)
{
}
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->dead == 0)
	{
		printf("je suis le philo : %d\n", philo->id);
	}	
	return (NULL);
}


int	main(int ac, char **av)
{
	t_program	program;
	
	check_arguments(ac, av, &program);
	mutexes_init(&program);
	if (philos_init(av, &program) == 0)
		return (1);
	while (program.num_of_philos--)
		pthread_join(program.philos[program.num_of_philos].thread, NULL);
}