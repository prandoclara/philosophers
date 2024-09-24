/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:17:38 by claprand          #+#    #+#             */
/*   Updated: 2024/09/24 16:31:21 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(char *s, t_philo *philo)
{
	uint64_t	time;

	time = get_time() - philo->table->start_simulation;
	printf("%lu %d %s", time, philo->id, s);
}

void	define_status(t_table *table, t_philo *philo, char *action)
{
	pthread_mutex_lock(&table->status_mutex);
	if (philo_died(table))
	{
		pthread_mutex_unlock(&table->status_mutex);
		return ;
	}
	write_status(action, philo);
	pthread_mutex_unlock(&table->status_mutex);
}
