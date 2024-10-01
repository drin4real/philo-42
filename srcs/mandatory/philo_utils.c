/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:50:04 by dbislimi          #+#    #+#             */
/*   Updated: 2024/10/01 16:03:18 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_free_philo(t_table *table, char *msg)
{
	if (table->philos)
		free(table->philos);
	destroy_mutexes(table);
	if (msg)
		printf("%s%s%s\n", R, msg, RST);
}
