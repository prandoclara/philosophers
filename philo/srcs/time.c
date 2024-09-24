/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:45:09 by claprand          #+#    #+#             */
/*   Updated: 2024/09/24 16:59:01 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0))
		error_msg("Erreur get_time");
	return (((uint64_t)tv.tv_sec * 1000) + ((uint64_t)tv.tv_usec / 1000));
}

int	ft_usleep(t_table *table, __useconds_t microsec)
{
	uint64_t	time_ms;

	time_ms = get_time();
	while (get_time() - time_ms < microsec)
	{
		pthread_mutex_lock(&table->dead_mutex);
		if (table->dead_philo == 1)
		{
			pthread_mutex_unlock(&table->dead_mutex);
			return (0);
		}
		pthread_mutex_unlock(&table->dead_mutex);
		usleep(10);
	}
	return (1);
}
