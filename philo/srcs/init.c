/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:11 by claprand          #+#    #+#             */
/*   Updated: 2024/09/24 16:44:50 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(int ac, char **av, t_table *table)
{
	table->nb_philo = ft_atoi(av[1]);
	table->ttd = ft_atoi(av[2]);
	table->tte = ft_atoi(av[3]);
	table->tts = ft_atoi(av[4]);
	table->done_eating = 0;
	table->dead_philo = 0;
	if (ac == 6)
		table->nb_meal = ft_atoi(av[5]);
	else
		table->nb_meal = -1;
	table->start_simulation = get_time();
	return (0);
}

int	init_philo(t_table *table)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!philo)
		return (error_msg("error init_philo"), 1);
	table->philo = philo;
	init_philo_util(table);
	return (0);
}

int	init_philo_util(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->philo[i].fork_left, NULL))
			return (clean_exit("Error init fork mutex", table));
		if (pthread_mutex_init(&table->philo[i].meal_mutex, NULL))
			return (clean_exit("Error init meal mutex", table));
		table->philo[i].table = table;
		table->philo[i].id = i + 1;
		table->philo[i].meal_count = 0;
	}
	i = -1;
	while (++i < table->nb_philo - 1)
		table->philo[i].fork_right = &table->philo[i + 1].fork_left;
	table->philo[i].fork_right = &table->philo[0].fork_left;
	return (0);
}

int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->dead_mutex, NULL))
		return (clean_exit("Error init dead mutex", table));
	if (pthread_mutex_init(&table->status_mutex, NULL))
		return (clean_exit("Error init status mutex", table));
	if (pthread_mutex_init(&table->nb_meal_reached_mutex, NULL))
		return (clean_exit("Error init nb meal reached mutex", table));
	return (0);
}
