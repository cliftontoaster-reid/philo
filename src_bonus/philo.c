/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:34:29 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/07 13:05:59 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\nUsage: %s <num_", argv[0]);
		printf("philosophers> <time_to_die> <time_to_eat>");
		printf(" <time_to_sleep> [<eat_limit>]\n");
		return (0);
	}
	return (1);
}

static int	setup_philosophers(t_simulation *sim, t_arg ***args)
{
	int	i;

	*args = malloc(sizeof(t_arg *) * sim->num_philosophers);
	if (!*args)
		return (0);
	i = 0;
	while (i < sim->num_philosophers)
	{
		sim->philosophers[i] = create_philosopher(i, sim);
		(*args)[i] = malloc(sizeof(t_arg));
		if (!(*args)[i])
		{
			while (--i >= 0)
				free((*args)[i]);
			free(*args);
			return (0);
		}
		(*args)[i]->philosopher = sim->philosophers[i];
		(*args)[i]->simulation = sim;
		if (pthread_create(&sim->philosophers[i]->thread, NULL,
				philosopher_routine, (*args)[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

static void	wait_and_cleanup(t_simulation *sim, t_arg **args)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_join(sim->philosophers[i]->thread, NULL);
		free(args[i]);
		i++;
	}
	cleanup(sim, args);
}

int	main(int argc, char *argv[])
{
	t_simulation	*sim;
	t_arg			**args;

	if (!check_args(argc, argv))
		return (1);
	sim = create_simulation(argc, argv);
	if (!sim)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (sim == (void *)69)
	{
		return (0);
	}
	if (!setup_philosophers(sim, &args))
	{
		cleanup(sim, NULL);
		return (1);
	}
	wait_and_cleanup(sim, args);
	return (0);
}
