/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:53:32 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/03 19:06:33 by lfiorell         ###   ########.fr       */
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
	philosopher->left_fork = &sim->forks[id];
	philosopher->last_nom = get_timestamp();
	if (id == sim->num_philosophers - 1)
		philosopher->right_fork = &sim->forks[0];
	else
		philosopher->right_fork = &sim->forks[id + 1];
	return (philosopher);
}

static inline int	toeat(t_arg *args)
{
	t_philosopher	*phi;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	long			now;

	phi = args->philosopher;
	left = phi->left_fork;
	right = phi->right_fork;
	if (phi_print(args->simulation, phi->id, THINKING, phi))
		return (1);
	if (phi->time_to_think)
		usleep(phi->time_to_think * 1000);
	pthread_mutex_lock(left);
	if (phi_print(args->simulation, phi->id, TAKING_FORK, phi))
		return (1);
	pthread_mutex_lock(right);
	if (phi_print(args->simulation, phi->id, TAKING_FORK, phi))
		return (1);
	if (phi_print(args->simulation, phi->id, EATING, phi))
		return (1);
	now = get_timestamp();
	if (now - phi->last_nom > phi->time_to_die)
	{
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(right);
		phi_print(args->simulation, phi->id, DIED, phi);
		return (1);
	}
	phi->last_nom = now;
	phi->eat_count++;
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_arg			*args;
	t_philosopher	*phi;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	args = (t_arg *)arg;
	phi = args->philosopher;
	left = phi->left_fork;
	right = phi->right_fork;
	while (1)
	{
		if (toeat(args))
			return (NULL);
		if (phi->eat_count >= phi->eat_limit)
		{
			pthread_mutex_unlock(left);
			pthread_mutex_unlock(right);
			return (NULL);
		}
		usleep(phi->time_to_eat * 1000);
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
		if (phi_print(args->simulation, phi->id, SLEEPING, phi))
			return (NULL);
		usleep(phi->time_to_sleep * 1000);
	}
	return (NULL);
}
