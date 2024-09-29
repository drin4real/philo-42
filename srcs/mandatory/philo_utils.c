/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:50:04 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/29 17:30:00 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_exit(char *msg)
{
	printf("%s%s\n",R, msg);
	exit(1);
}

void	ft_error(t_table *table, char *msg)
{
	free(table->philos);
	free(table->forks);
	ft_exit(msg);
}
