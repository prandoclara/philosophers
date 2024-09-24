/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:22 by claprand          #+#    #+#             */
/*   Updated: 2024/09/24 16:36:40 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	error_msg(char *s)
{
	if (!s)
		return ;
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < (int)table->nb_philo)
	{
		pthread_mutex_destroy(&table->philo[i].fork_left);
		pthread_mutex_destroy(&table->philo[i].meal_mutex);
	}
	pthread_mutex_destroy(&table->status_mutex);
	pthread_mutex_destroy(&table->dead_mutex);
	pthread_mutex_destroy(&table->nb_meal_reached_mutex);
}

int	clean_exit(char *s, t_table *table)
{
	error_msg(s);
	if (table)
		destroy_mutexes(table);
	if (table->philo)
		free(table->philo);
	return (1);
}
