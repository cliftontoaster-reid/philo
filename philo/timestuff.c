/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:53:38 by lfiorell          #+#    #+#             */
/*   Updated: 2025/05/30 12:45:31 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

bool	is_dead(t_philo *philo, t_data *data)
{
	if (philo->data->stop)
		return (false);
	if (get_time(data) - philo->last_meal_time > data->time_to_die)
	{
		philo->data->dead_people++;
		return (true);
	}
	return (false);
}

long	get_time(t_data *data)
{
	long			time;
	struct timeval	current;

	gettimeofday(&current, NULL);
	time = current.tv_sec * 1000;
	time += current.tv_usec / 1000;
	pthread_mutex_lock(data->time_mutex);
	if (data->time == 0)
		data->time = time;
	pthread_mutex_unlock(data->time_mutex);
	return (time - data->time);
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
		usleep(10);
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000;
		elapsed += (current.tv_usec - start.tv_usec) / 1000;
	}
	(void)philo;
	return (0);
}
