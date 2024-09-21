/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:58:16 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/21 19:19:02 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	thinking(t_philo *philo)
{
	printf("%zu %d is thinking\n", get_current_time() - philo->start_time, philo->id);
}

void	sleeping(t_philo *philo)
{
	printf("%zu %d is sleeping\n", get_current_time() - philo->start_time, philo->id);
	ft_usleep(philo->table->time_to_sleep);
}

void	eating(t_philo *philo)
{
	long	time;
		
	pthread_mutex_lock(&philo->right->fork);
	printf("%zu %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
	pthread_mutex_lock(&philo->left->fork);
	time = get_current_time() - philo->start_time;
	printf("time %zu\n", time);
	printf("%zu %d has taken a fork\n", time, philo->id);
	philo->last_meal_time = time;
	printf("%zu %d is eating\n", time, philo->id);
	++philo->nb_of_meals;
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->right->fork);
	pthread_mutex_unlock(&philo->left->fork);
}
void	wait_all_threads(t_table *table)
{
	while (!table->all_threads_ready)
		;
}
void	*routine_philo(void *arg)
{
	t_philo	*philo;
	size_t	time;
	
	philo = (t_philo *)arg;
	wait_all_thread(philo->table);
	philo->start_time = philo->table->start_time;
	if (philo->id % 2 == 0)
		ft_usleep(5000);
	while (philo->table->dead == 0)
	{
		if (philo->full)
			break ;
		time = get_current_time() - philo->start_time;
		printf("philo %d\nlast meal : %zu\ncurrent time : %zu\ntime to die : %ld\n", philo->id, philo->last_meal_time , time, philo->table->time_to_die);
		if (philo->table->time_to_die < (philo->last_meal_time) )
		{
			philo->table->dead = 1;
			printf("%zu %d died\n", get_current_time() - philo->start_time, philo->id);
			break ;
		}
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
