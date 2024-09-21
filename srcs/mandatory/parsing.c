/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:37:05 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/21 18:56:03 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_atol_philo(char *s)
{
	int		i;
	size_t	res;
	int		sign;
	int		size;

	size = 0;
	res = 0;
	sign = 1;
	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		++i;
	while (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			sign *= -1;
	if (sign == -1)
		ft_exit(NEGATIVE);
	while (size <= 10 && (s[i] >= '0' && s[i] <= '9'))
	{
		res = res * 10 + (s[i] - '0');
		++size;
		++i;
	}
	if (res > INT_MAX || size > 10)
		ft_exit(INTMAX);
	return (res);
}

void	parsing(t_table *table, char **av)
{
	table->nb_of_philos = ft_atol_philo(av[1]);
	table->time_to_die = ft_atol_philo(av[2]);
	table->time_to_eat = ft_atol_philo(av[3]);
	table->time_to_sleep = ft_atol_philo(av[4]);
	if (av[5])
		table->nbr_limit_meal = ft_atol_philo(av[5]);
	else
		table->nbr_limit_meal = -1;
}
