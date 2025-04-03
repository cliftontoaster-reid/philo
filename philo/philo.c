/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:26:52 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/03 15:30:09 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	ft_strtoint(const char *str)
{
	int		i;
	int		sign;
	long	result;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result * sign > INT_MAX || result * sign < INT_MIN)
		return (-1);
	return ((int)(result * sign));
}

static int	setup_malocs(t_simulation *sim)
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
			// cleanup
			return (0);
		}
		i++;
	}
	sim->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!sim->print_mutex)
	{
		free(sim->forks);
		free(sim->philosophers);
		return (0);
	}
	if (pthread_mutex_init(sim->print_mutex, NULL) != 0)
	{
		free(sim->print_mutex);
		free(sim->forks);
		free(sim->philosophers);
		return (0);
	}
	sim->death_check = malloc(sizeof(pthread_mutex_t));
	if (!sim->death_check)
	{
		free(sim->forks);
		free(sim->philosophers);
		return (0);
	}
	if (pthread_mutex_init(sim->death_check, NULL) != 0)
	{
		free(sim->death_check);
		free(sim->forks);
		free(sim->philosophers);
		return (0);
	}
	return (1);
}

t_simulation	*create_simulation(int argc, char **argv)
{
	t_simulation	*sim;

	sim = (t_simulation *)malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	memset(sim, 0, sizeof(t_simulation));
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
		free(sim);
		return (NULL);
	}
	if (!setup_malocs(sim))
	{
		free(sim);
		return (NULL);
	}
	return (sim);
}

void	cleanup(t_simulation *sim, t_arg **args)
{
	int	i;

	if (!sim)
		return ;
	// Clean up the print mutex
	if (sim->print_mutex)
	{
		pthread_mutex_destroy(sim->print_mutex);
		free(sim->print_mutex);
	}
	// Free the philosophers
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
	// Destroy the forks
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
	if (sim->death_check)
	{
		pthread_mutex_destroy(sim->death_check);
		free(sim->death_check);
	}
	// Free the simulation itself
	free(sim);
	// Free any remaining args that weren't freed in main
	if (args)
	{
		free(args);
	}
}

int	main(int argc, char *argv[])
{
	t_simulation	*sim;
	t_arg			**args;
	int				i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\nUsage: %s <num_", argv[0]);
		printf("philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<eat_limit>]\n");
		return (1);
	}
	sim = create_simulation(argc, argv);
	if (!sim)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	// Allocate args array to keep track of all args
	args = malloc(sizeof(t_arg *) * sim->num_philosophers);
	if (!args)
	{
		// Cleanup
		return (1);
	}
	// Initialize each philosopher and create threads
	i = 0;
	while (i < sim->num_philosophers)
	{
		sim->philosophers[i] = create_philosopher(i, sim);
		args[i] = malloc(sizeof(t_arg));
		if (!args[i])
		{
			// Clean up previously allocated memory
			while (--i >= 0)
				free(args[i]);
			free(args);
			// Cleanup
			return (1);
		}
		args[i]->philosopher = sim->philosophers[i];
		args[i]->simulation = sim;
		if (pthread_create(&sim->philosophers[i]->thread, NULL,
				philosopher_routine, args[i]) != 0)
		{
			// Cleanup
			return (1);
		}
		i++;
	}
	// Join all threads separately after creation
	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_join(sim->philosophers[i]->thread, NULL);
		free(args[i]);
		i++;
	}
	// Wait until one philosopher dies, if so, end all threads
	cleanup(sim, args);
	return (0);
}
