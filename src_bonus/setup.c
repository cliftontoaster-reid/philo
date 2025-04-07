/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:33:31 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/07 13:01:22 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_arguments(t_simulation *sim, int argc, char **argv)
{
	sim->num_philosophers = ft_strtoint(argv[1]);
	sim->time_to_die = ft_strtoint(argv[2]);
	sim->time_to_eat = ft_strtoint(argv[3]);
	sim->time_to_sleep = ft_strtoint(argv[4]);
	if (argc == 6)
		sim->eat_limit = ft_strtoint(argv[5]);
	else
		sim->eat_limit = INT_MAX;
	if (sim->num_philosophers <= 0 || sim->time_to_die <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0
		|| sim->eat_limit <= 0)
	{
		return (0);
	}
	return (1);
}

t_philosopher	*create_philosopher(int id, t_simulation *sim)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	memset(philosopher, 0, sizeof(t_philosopher));
	philosopher->id = id;
	philosopher->eat_count = 0;
	philosopher->eat_limit = sim->eat_limit;
	philosopher->time_to_think = sim->time_to_think;
	philosopher->time_to_eat = sim->time_to_eat;
	philosopher->time_to_sleep = sim->time_to_sleep;
	philosopher->time_to_die = sim->time_to_die;
	return (philosopher);
}

t_simulation	*create_simulation(int argc, char **argv)
{
	t_simulation	*sim;

	sim = (t_simulation *)malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	memset(sim, 0, sizeof(t_simulation));
	if (!parse_arguments(sim, argc, argv))
	{
		free(sim);
		return (NULL);
	}
	if (sim->num_philosophers == 1)
	{
		printf("%ld %d has taken a fork\n", get_timestamp(), 1);
		usleep(sim->time_to_die * 1000);
		printf("%ld %d died\n", get_timestamp(), 1);
		cleanup(sim, NULL);
		return ((void *)69);
	}
	if (!setup_malocs(sim))
	{
		free(sim);
		return (NULL);
	}
	return (sim);
}

static int	setup_phis(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		sim->philosophers[i] = create_philosopher(i, sim);
		if (!sim->philosophers[i])
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
	sim->philosophers = malloc(sizeof(t_philosopher *) * sim->num_philosophers);
	if (!sim->philosophers)
		return (0);
	if (sem_init(&sim->forks, 0, sim->num_philosophers) != 0)
	{
		free(sim->philosophers);
		return (0);
	}
	if (sem_init(&sim->print_mutex, 0, 1) != 0)
	{
		sem_destroy(&sim->forks);
		free(sim->philosophers);
		return (0);
	}
	if (setup_phis(sim) == 0)
		return (0);
	return (1);
}
