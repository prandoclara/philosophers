/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:21:54 by claprand          #+#    #+#             */
/*   Updated: 2024/09/25 11:20:34 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_forks(t_table *table, t_philo *philo)
{
	if (philo->id % 2)
	{
		if (&philo->fork_left == philo->fork_right)
		{
			define_status(table, philo, FORK_L);
			return (1);
		}
		pthread_mutex_lock(&philo->fork_left);
		define_status(table, philo, FORK_L);
		pthread_mutex_lock(philo->fork_right);
		define_status(table, philo, FORK_R);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		define_status(table, philo, FORK_R);
		pthread_mutex_lock(&philo->fork_left);
		define_status(table, philo, FORK_L);
	}
	return (0);
}
