/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:34:31 by claprand          #+#    #+#             */
/*   Updated: 2024/09/25 11:43:03 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>
# include <limits.h>
# include <string.h>

# define DIED "died\n"
# define EATING "is eating\n"
# define SLEEPING "is sleeping\n"
# define THINKING "is thinking\n"
# define FORK_R "has taken a fork\n"
# define FORK_L "has taken a fork\n"

typedef struct s_philo	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	int				nb_philo;
	int				done_eating;
	unsigned int	nb_meal;
	unsigned int	dead_philo;
	uint64_t		ttd;
	uint64_t		tte;
	uint64_t		tts;
	uint64_t		start_simulation;
	uint64_t		eating;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	nb_meal_reached_mutex;
}	t_table;

typedef struct s_philo
{
	t_table			*table;
	unsigned int	id;
	unsigned int	meal_count;
	uint64_t		last_meal;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
	pthread_t		philo_thread_id;
}	t_philo;

/*PARSING*/
int			is_digit(char *s);
int			ft_atoi(char *s);
int			is_valid_input(int ac, char **av);

/*TIME*/
uint64_t	get_time(void);
int			ft_usleep(t_table *table, __useconds_t microsec);

/*INIT*/
int			init_table(int ac, char **av, t_table *table);
int			init_philo(t_table *table);
int			init_philo_util(t_table *table);
int			init_mutexes(t_table *table);

/*UTILS*/
size_t		ft_strlen(const char *s);
void		error_msg(char *s);
int			clean_exit(char *s, t_table *table);
void		destroy_mutexes(t_table *table);

/*START*/
void		monitoring_util(t_table *table, int i);
int			monitoring(t_table *table);
int			create_threads(t_table *table);
int			start_simulation(t_table *table);

/*ROUTINE*/
int			philo_died(t_table *table);
void		*routine(void *philo_pointer);
void		sleep_routine(t_table *table, t_philo *philo);
int			eat_routine(t_table *table, t_philo *philo);
void		think_routine(t_table *table, t_philo *philo);

/*FORK*/
int			lock_forks(t_table *table, t_philo *philo);

/*STATUS*/
void		write_status(char *s, t_philo *philo);
void		define_status(t_table *table, t_philo *philo, char *action);

#endif 
