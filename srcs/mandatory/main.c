/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:12:58 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/18 18:56:52 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// void	*monitor(void *arg)
// {
// 	t_program	*pro;
// 	int	i;

// 	pro = (t_program *)arg;
// 	i = 0;
// 	while (pro->philos[i])
// 	{
		
// 	}
	
// }

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->start_time = get_current_time();
	if (philo->id % 2 == 1)
		ft_usleep(5000);
	while (*philo->dead == 0)
	{
		
		eat(philo);
		
		printf("%zu %d is sleeping\n", get_current_time() - philo->start_time, philo->id);
		ft_usleep(philo->time_to_sleep);
	
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