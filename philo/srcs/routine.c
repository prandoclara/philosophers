/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:12:50 by claprand          #+#    #+#             */
/*   Updated: 2024/09/24 16:59:14 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_table *table)
{
	int	died;

	pthread_mutex_lock(&table->dead_mutex);
	died = table->dead_philo;
	pthread_mutex_unlock(&table->dead_mutex);
	return (died);
}

int	eat_routine(t_table *table, t_philo *philo)
{
	define_status(table, philo, EATING);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(table, table->tte);
	philo->meal_count++;
	if (philo->meal_count == table->nb_meal)
	{
		pthread_mutex_lock(&table->nb_meal_reached_mutex);
		table->done_eating++;
		pthread_mutex_unlock(&table->nb_meal_reached_mutex);
		pthread_mutex_unlock(&philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

void	think_routine(t_table *table, t_philo *philo)
{
	uint64_t	ttt;

	pthread_mutex_lock(&philo->meal_mutex);
	ttt = (table->ttd - (get_time() - philo->last_meal) - table->tte) / 2;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (ttt < 0)
		ttt = 0;
	if (ttt > 600)
		ttt = 200;
	define_status(table, philo, THINKING);
	ft_usleep(table, ttt);
}

void	sleep_routine(t_table *table, t_philo *philo)
{
	define_status(table, philo, SLEEPING);
	ft_usleep(table, table->tts);
	define_status(table, philo, THINKING);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;
	t_table	*table;

	philo = philo_pointer;
	table = philo->table;
	if (philo->id % 2 && table->nb_philo > 1)
		think_routine(table, philo);
	while (!philo_died(table))
	{
		if (table->nb_philo % 2 && philo->meal_count)
			ft_usleep(table, (table->ttd - (table->tte + table->tts)) * 0.5);
		if (lock_forks(table, philo))
			break ;
		if (eat_routine(table, philo))
			return (0);
		sleep_routine(table, philo);
	}
	return (0);
}
