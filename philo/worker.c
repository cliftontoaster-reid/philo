/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:53:32 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/03 15:42:03 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

long	get_timestamp(void)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (timestamp);
}

int	phi_print(t_simulation *sim, int idx, t_state state, t_philosopher *phi)
{
	char	*state_str;
	int		should_print;

	pthread_mutex_lock(sim->death_check);
	if (sim->finished_philosophers > 0 && state != DIED)
	{
		pthread_mutex_unlock(phi->left_fork);
		pthread_mutex_unlock(phi->right_fork);
		pthread_mutex_unlock(sim->death_check);
		return (1);
	}
	should_print = 1;
	if (state == THINKING)
		state_str = "is thinking";
	else if (state == EATING)
		state_str = "is eating";
	else if (state == SLEEPING)
		state_str = "is sleeping";
	else if (state == DIED)
	{
		sim->finished_philosophers++;
		state_str = "died";
	}
	else
		should_print = 0;
	if (should_print)
	{
		pthread_mutex_lock(sim->print_mutex);
		printf("%ld %d %s\n", get_timestamp(), idx + 1, state_str);
		pthread_mutex_unlock(sim->print_mutex);
	}
	pthread_mutex_unlock(sim->death_check);
	return (state == DIED || sim->finished_philosophers > 0);
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

void	*philosopher_routine(void *arg)
{
	t_arg			*args;
	t_philosopher	*phi;

	args = (t_arg *)arg;
	phi = args->philosopher;
	while (1)
	{
		if (phi_print(args->simulation, phi->id, THINKING, phi))
			return (NULL);
		usleep(phi->time_to_think * 1000);
		pthread_mutex_lock(phi->left_fork);
		pthread_mutex_lock(phi->right_fork);
		if (phi_print(args->simulation, phi->id, EATING, phi))
			return (NULL);
		if (get_timestamp() - phi->last_nom > phi->time_to_die)
		{
			pthread_mutex_unlock(phi->left_fork);
			pthread_mutex_unlock(phi->right_fork);
			phi_print(args->simulation, phi->id, DIED, phi);
			return (NULL);
		}
		phi->last_nom = get_timestamp();
		phi->eat_count++;
		if (phi->eat_count >= phi->eat_limit)
		{
			pthread_mutex_unlock(phi->left_fork);
			pthread_mutex_unlock(phi->right_fork);
			return (NULL);
		}
		usleep(phi->time_to_eat * 1000);
		pthread_mutex_unlock(phi->right_fork);
		pthread_mutex_unlock(phi->left_fork);
		if (phi_print(args->simulation, phi->id, SLEEPING, phi))
			return (NULL);
		usleep(phi->time_to_sleep * 1000);
	}
	return (NULL);
}
