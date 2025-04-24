/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:53:38 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/24 15:03:16 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

bool	is_dead(t_philo *philo, t_data *data)
{
	if (philo->meals_eaten >= data->max_meals)
		return (false);
	if (get_time(data) - philo->last_meal_time > data->time_to_die)
	{
		print(philo, DEAD);
		return (true);
	}
	return (false);
}

long	get_time(t_data *data)
{
	long	time;

	pthread_mutex_lock(data->time_mutex);
	time = data->time;
	pthread_mutex_unlock(data->time_mutex);
	return (time);
}

// use usleep to wait for a duration in milliseconds
// then increment the time in the data structure if needed
long	phi_wait(long duration, t_philo *philo)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;

	gettimeofday(&start, NULL);
	elapsed = 0;
	while (elapsed < duration)
	{
		usleep(100);
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000;
		elapsed += (current.tv_usec - start.tv_usec) / 1000;
	}
	pthread_mutex_lock(philo->data->time_mutex);
	philo->local_time += duration;
	if (philo->local_time > philo->data->time)
		philo->data->time = philo->local_time;
	pthread_mutex_unlock(philo->data->time_mutex);
	return (philo->local_time);
}
