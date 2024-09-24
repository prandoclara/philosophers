/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:36:28 by claprand          #+#    #+#             */
/*   Updated: 2024/09/24 16:59:39 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (is_valid_input(ac, av) != 0)
		return (1);
	if (init_table(ac, av, &table) != 0)
		return (1);
	if (start_simulation(&table))
		return (1);
	return (0);
}
