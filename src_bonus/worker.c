/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:02:34 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/07 13:05:05 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	toeat(t_arg *args)
{
	t_philosopher	*phi;
	long			now;

	phi = args->philosopher;
	if (phi_print(args->simulation, phi->id, THINKING))
		return (1);
	sem_wait(&args->simulation->forks);
	if (phi_print(args->simulation, phi->id, TAKING_FORK))
		return (1);
	sem_wait(&args->simulation->forks);
	if (phi_print(args->simulation, phi->id, TAKING_FORK))
		return (1);
	now = get_timestamp();
	if (now - phi->last_nom > phi->time_to_die)
	{
		sem_post(&args->simulation->forks);
		sem_post(&args->simulation->forks);
		phi_print(args->simulation, phi->id, DIED);
		return (1);
	}
	if (phi_print(args->simulation, phi->id, EATING))
		return (1);
	phi->last_nom = now;
	phi->eat_count++;
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_arg			*args;
	t_philosopher	*phi;

	args = (t_arg *)arg;
	phi = args->philosopher;
	phi->last_nom = get_timestamp();
	while (1)
	{
		if (toeat(args))
			return (NULL);
		if (phi->eat_count >= phi->eat_limit)
		{
			sem_post(&args->simulation->forks);
			sem_post(&args->simulation->forks);
			return (NULL);
		}
		usleep(phi->time_to_eat * 1000);
		sem_post(&args->simulation->forks);
		sem_post(&args->simulation->forks);
		if (phi_print(args->simulation, phi->id, SLEEPING))
			return (NULL);
		usleep(phi->time_to_sleep * 1000);
	}
	return (NULL);
}
