/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:58:16 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/29 18:22:33 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	end_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_dead);
	if (philo->table->dead)
	{
		pthread_mutex_unlock(&philo->table->check_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->check_dead);
	return (philo->full);
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
	if (philo->table->nb_of_philos == 1)
		return (1);
	pthread_mutex_lock(philo->left);
	if (end_simulation(philo))
		return (1);
	time = get_current_time() - philo->start;
	printf("%zu %d has taken a fork\n", time, philo->id);
	pthread_mutex_lock(&philo->table->check_meals[philo->id - 1]);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->table->check_meals[philo->id - 1]);
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
	
	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	philo->start = philo->table->start_time;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!end_simulation(philo))
	{
		if (eating(philo) || sleeping(philo) || thinking(philo))
			break ;
	}
	return (NULL);
}

void	*routine_checker(void *arg)
{
	size_t	i;
	size_t	time;
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		// i = -1;
		// while (++i < table->nb_of_philos)
		// {
		// 	time = get_current_time() - table->start_time;
		// 	pthread_mutex_lock(&table->check_meals[i]);
		// 	if (table->time_to_die <= time - table->philos[i].last_meal_time)
		// 	{
		// 		pthread_mutex_lock(&table->check_dead);
		// 		table->dead = 1;
		// 		pthread_mutex_unlock(&table->check_dead);
		// 		printf("%zu %d died\n", time, table->philos[i].id);
		// 		pthread_mutex_unlock(&table->check_meals[i]);
		// 		return (NULL);
		// 	}	
		// 	pthread_mutex_unlock(&table->check_meals[i]);
		// }
		i = -1;
		while (++i < table->nb_of_philos)
		{
			time = get_current_time() - table->start_time;
			pthread_mutex_lock(&table->check_meals[i]);
			if (table->time_to_die <= time - table->philos[i].last_meal_time)
			{
				pthread_mutex_lock(&table->check_dead);
				table->dead = 1;
				pthread_mutex_unlock(&table->check_dead);
				printf("%zu %d died\n", time, table->philos[i].id);
				pthread_mutex_unlock(&table->check_meals[i]);
				return (NULL);
			}	
			pthread_mutex_unlock(&table->check_meals[i]);
		}
	}
	return (NULL);
}
