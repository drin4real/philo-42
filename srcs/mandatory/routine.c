/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:58:16 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/18 18:20:27 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*routine_philo(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	printf("Hi im philo %d\n", philo->id);
	return (NULL);
}