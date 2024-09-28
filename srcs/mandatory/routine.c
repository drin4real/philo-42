/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:58:16 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/25 19:16:58 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	end_simulation(t_philo *philo)
{
	return (philo->table->dead || philo->full);
}

int	thinking(t_philo *philo)
{
	if (end_simulation(philo))
		return (1);
	printf("%zu %d is thinking\n", get_current_time() - philo->start, philo->id);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (end_simulation(philo))
		return (1);
	printf("%zu %d is sleeping\n", get_current_time() - philo->start, philo->id);
	ft_usleep(philo->table->time_to_sleep);
	return (0);
}

int	eating(t_philo *philo)
{
	long	time;
	
	if (end_simulation(philo))
		return (1);
	pthread_mutex_lock(philo->right);
	if (end_simulation(philo))
		return (1);
	printf("%zu %d has taken a fork\n", get_current_time() - philo->start, philo->id);
	pthread_mutex_lock(philo->left);
	if (end_simulation(philo))
		return (1);
	time = get_current_time() - philo->start;
	printf("%zu %d has taken a fork\n", time, philo->id);
	// pthread_mutex_lock(&philo->table->check_meals[philo->id - 1]);
	philo->last_meal_time = time;
	// pthread_mutex_unlock(&philo->table->check_meals[philo->id - 1]);
	printf("%zu %d is eating\n", time, philo->id);
	ft_usleep(philo->table->time_to_eat);
	if (++philo->nb_of_meals == philo->table->nbr_limit_meal)
		philo->full = true;
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (0);
}
void	wait_all_threads(t_table *table)
{
	pthread_mutex_lock(&table->ready);
	pthread_mutex_unlock(&table->ready);
}
void	*routine_philo(void *arg)
{
	t_philo	*philo;
	size_t	time;
	
	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	// pthread_mutex_lock(&philo->table->ready);
	philo->start = philo->table->start_time;
	printf("p %ld\n", philo->start);
	// pthread_mutex_unlock(&philo->table->ready);
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!end_simulation(philo))
	{
		time = get_current_time() - philo->start;
		// if (philo->table->time_to_die < time - philo->last_meal_time)
		// {
		// 	philo->table->dead = 1;
		// 	printf("%zu %d died\n", time, philo->id);
		// 	break ;
		// }
		if (eating(philo) || sleeping(philo) || thinking(philo))
			break ;
	}
	return (NULL);
}

void	*routine_checker(void *arg)
{
	size_t	i;
	// size_t	time;
	t_table	*table;

	table = (t_table *)arg;
	// printf("check %d\n", table->dead);
	printf("c %ld\n", table->start_time);
	while (1)
	{
		i = 0;
		//time = get_current_time() - table->start_time;
		while (i < table->nb_of_philos)
		{
			//printf("k %ld\n", (get_current_time() - table->start_time) - table->philos[i].last_meal_time);
			// pthread_mutex_lock(&table->check_meals[i]);
			if (table->time_to_die < (get_current_time() - table->start_time) - table->philos[i].last_meal_time)
			{
				table->dead = 1;
				printf("%zu %d died\n", get_current_time() - table->start_time, table->philos[i].id);
				// pthread_mutex_unlock(&table->check_meals[i]);
				break ;
			}	
			++i;
			// pthread_mutex_unlock(&table->check_meals[i]);
		}
	}
	return (NULL);
}
