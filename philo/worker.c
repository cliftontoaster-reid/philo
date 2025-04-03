/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:53:32 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/03 11:36:29 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <sys/time.h>

long	get_timestamp(void)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (timestamp);
}

void	phi_print(t_simulation *sim, int idx, t_state state)
{
	char	*state_str;

	if (state == THINKING)
		state_str = "is thinking";
	else if (state == EATING)
		state_str = "is eating";
	else if (state == SLEEPING)
		state_str = "is sleeping";
	else
		state_str = "died";
	pthread_mutex_lock(&sim->print_mutex);
	printf("%ld %d %s\n", get_timestamp(), idx + 1, state_str);
	pthread_mutex_unlock(&sim->print_mutex);
}

t_philosopher	*create_philosopher(int id, t_simulation *sim)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
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

void	free_philosopher(t_philosopher *philosopher)
{
	if (philosopher)
		free(philosopher);
}

void	*philosopher_routine(void *arg)
{
	t_arg			*args;
	t_philosopher	*phi;

	args = (t_arg *)arg;
	phi = args->philosopher;
	while (1)
	{
		phi_print(args->simulation, phi->id, THINKING);
		usleep(phi->time_to_think * 1000);
		pthread_mutex_lock(phi->left_fork);
		pthread_mutex_lock(phi->right_fork);
		phi_print(args->simulation, phi->id, EATING);
		if (phi->time_to_die - get_timestamp() > 0)
		{
			phi->last_nom = get_timestamp();
			phi->eat_count++;
			if (phi->eat_count >= phi->eat_limit)
			{
				pthread_mutex_unlock(phi->left_fork);
				pthread_mutex_unlock(phi->right_fork);
				return (NULL);
			}
		}
		else
		{
			pthread_mutex_unlock(phi->left_fork);
			pthread_mutex_unlock(phi->right_fork);
			phi_print(args->simulation, phi->id, DIED);
			return (NULL);
		}
		usleep(phi->time_to_eat * 1000);
		pthread_mutex_unlock(phi->right_fork);
		pthread_mutex_unlock(phi->left_fork);
		phi_print(args->simulation, phi->id, SLEEPING);
		usleep(phi->time_to_sleep * 1000);
	}
	return (NULL);
}
