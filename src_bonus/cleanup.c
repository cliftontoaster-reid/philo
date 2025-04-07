/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:53:45 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/07 12:45:31 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	cleanup_print_mutex(t_simulation *sim)
{
	sem_destroy(&sim->print_mutex);
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
	sem_destroy(&sim->forks);
}

void	cleanup(t_simulation *sim, t_arg **args)
{
	if (!sim)
		return ;
	cleanup_print_mutex(sim);
	cleanup_philosophers(sim);
	cleanup_forks(sim);
	free(sim);
	if (args)
		free(args);
}
