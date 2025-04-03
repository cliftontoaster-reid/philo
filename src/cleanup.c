/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:53:45 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/03 16:53:49 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_print_mutex(t_simulation *sim)
{
	if (sim->print_mutex)
	{
		pthread_mutex_destroy(sim->print_mutex);
		free(sim->print_mutex);
	}
}

static void	cleanup_philosophers(t_simulation *sim)
{
	int	i;

	if (sim->philosophers)
	{
		i = 0;
		while (i < sim->num_philosophers)
		{
			if (sim->philosophers[i])
				free(sim->philosophers[i]);
			i++;
		}
		free(sim->philosophers);
	}
}

static void	cleanup_forks(t_simulation *sim)
{
	int	i;

	if (sim->forks)
	{
		i = 0;
		while (i < sim->num_philosophers)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
		free(sim->forks);
	}
}

static void	cleanup_death_check(t_simulation *sim)
{
	if (sim->death_check)
	{
		pthread_mutex_destroy(sim->death_check);
		free(sim->death_check);
	}
}

void	cleanup(t_simulation *sim, t_arg **args)
{
	if (!sim)
		return ;
	cleanup_print_mutex(sim);
	cleanup_philosophers(sim);
	cleanup_forks(sim);
	cleanup_death_check(sim);
	free(sim);
	if (args)
		free(args);
}
