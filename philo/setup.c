/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:57:12 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/03 16:57:21 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setup_malocs2(t_simulation *sim)
{
	int	i;

	sim->philosophers = malloc(sizeof(t_philosopher *) * sim->num_philosophers);
	if (!sim->philosophers)
		return (0);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->num_philosophers);
	if (!sim->forks)
	{
		free(sim->philosophers);
		return (0);
	}
	i = 0;
	while (i < sim->num_philosophers)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			sim->num_philosophers = i;
			cleanup(sim, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

int	setup_malocs(t_simulation *sim)
{
	if (setup_malocs2(sim) == 0)
		return (0);
	sim->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!sim->print_mutex)
	{
		cleanup(sim, NULL);
		return (0);
	}
	if (pthread_mutex_init(sim->print_mutex, NULL) != 0)
	{
		cleanup(sim, NULL);
		return (0);
	}
	sim->death_check = malloc(sizeof(pthread_mutex_t));
	if (!sim->death_check)
	{
		cleanup(sim, NULL);
		return (0);
	}
	if (pthread_mutex_init(sim->death_check, NULL) != 0)
	{
		cleanup(sim, NULL);
		return (0);
	}
	return (1);
}
