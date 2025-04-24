/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:02:47 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/24 16:41:11 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline bool	handle_oof(t_philo *philo)
{
	bool	oof;

	oof = is_dead(philo, philo->data);
	if (oof)
	{
		print(philo, DEAD);
		philo->data->dead_people++;
		return (true);
	}
	return (false || philo->data->dead_people > 0);
}

inline void	phi_think(t_philo *philo)
{
	print(philo, THINKING);
}

static void	phi_nomnomnom(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		print(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		print(philo, FORK);
	}
	pthread_mutex_lock(philo->data->time_mutex);
	philo->last_meal_time = philo->data->time;
	pthread_mutex_unlock(philo->data->time_mutex);
	print(philo, EATING);
	philo->meals_eaten++;
	phi_wait(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	phi_mimimimimi(t_philo *philo)
{
	print(philo, SLEEPING);
	phi_wait(philo->data->time_to_sleep, philo);
}

void	*philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->data->time_mutex);
	philo->last_meal_time = philo->data->time;
	pthread_mutex_unlock(philo->data->time_mutex);
	if (philo->data->num_philos == 1)
	{
		print(philo, FORK);
		phi_wait(philo->data->time_to_die, philo);
		print(philo, DEAD);
		return (NULL);
	}
	if (philo->id % 2 != 0)
		usleep(1000);
	while (true)
	{
		if (handle_oof(philo))
			return (NULL);
		phi_think(philo);
		phi_nomnomnom(philo);
		if (handle_oof(philo))
			return (NULL);
		phi_mimimimimi(philo);
	}
	return (NULL);
}
