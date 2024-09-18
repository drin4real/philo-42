/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:50:04 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/18 17:53:22 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_exit(char *msg)
{
	ft_printf(R"%s\n", msg);
	exit(1);
}

void	ft_error(t_table *table, char *msg)
{
	free(table->philos);
	free(table->forks);
	ft_exit(msg);
}
