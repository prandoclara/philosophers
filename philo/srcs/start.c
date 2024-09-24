/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:55:45 by claprand          #+#    #+#             */
/*   Updated: 2024/09/24 16:40:27 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring_util(t_table *table, int i)
{
	pthread_mutex_lock(&table->philo[i].meal_mutex);
	table->eating = get_time() - table->philo[i].last_meal;
	pthread_mutex_unlock(&table->philo[i].meal_mutex);
}

int	monitoring(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		monitoring_util(table, i);
		if (table->eating >= table->ttd)
		{
			pthread_mutex_lock(&table->dead_mutex);
			table->dead_philo = 1;
			pthread_mutex_unlock(&table->dead_mutex);
			pthread_mutex_lock(&table->status_mutex);
			write_status(DIED, &table->philo[i]);
			pthread_mutex_unlock(&table->status_mutex);
			break ;
		}
		pthread_mutex_lock(&table->nb_meal_reached_mutex);
		if (table->done_eating == table->nb_philo)
			return (pthread_mutex_unlock(&table->nb_meal_reached_mutex), 0);
		pthread_mutex_unlock(&table->nb_meal_reached_mutex);
		if (i == table->nb_philo - 1)
			i = -1;
		usleep(20);
	}
	return (0);
}

int	create_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		table->philo[i].last_meal = table->start_simulation;
		if (pthread_create(&table->philo[i].philo_thread_id, NULL,
				routine, &table->philo[i]))
			return (clean_exit("Error create_threads", table));
	}
	monitoring(table);
	i = -1;
	while (++i < table->nb_philo)
	{
		if (pthread_join(table->philo[i].philo_thread_id, NULL))
			return (clean_exit("Error join philo", table));
	}
	return (0);
}

int	start_simulation(t_table *table)
{
	if (init_philo(table))
		return (error_msg("init_philo"), 1);
	if (init_mutexes(table))
		return (error_msg("init_table"), 1);
	if (create_threads(table))
		return (error_msg("threading"), 1);
	clean_exit(NULL, table);
	return (0);
}
