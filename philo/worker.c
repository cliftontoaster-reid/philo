/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:02:47 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/26 15:43:17 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline bool	handle_oof(t_philo *philo)
{
	bool	oof;

	oof = is_dead(philo, philo->data);
	if (oof)
	{
		philo->data->dead_people++;
		print(philo, DEAD);
		return (true);
	}
	return (false || philo->data->dead_people > 0);
}

static inline bool	check_max_meals(t_philo *philo)
{
	int	i;

	if (philo->meals_eaten < philo->data->max_meals)
		return (false);
	i = 0;
	while (i < philo->data->num_philos)
	{
		if (philo->data->philos[i]->meals_eaten < philo->data->max_meals)
		{
			pthread_mutex_unlock(philo->data->time_mutex);
			return (false);
		}
		i++;
	}
	philo->data->stop = true;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (true);
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
	philo->last_meal_time = get_time(philo->data);
	print(philo, EATING);
	philo->meals_eaten++;
	if (check_max_meals(philo))
		return ;
	phi_wait(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*phi_mimimimimi(t_philo *philo)
{
	if (philo->data->stop)
		return (NULL);
	if (handle_oof(philo))
		return (NULL);
	print(philo, THINKING);
	if (philo->data->stop)
		return (NULL);
	phi_nomnomnom(philo);
	if (philo->data->stop)
		return (NULL);
	if (handle_oof(philo))
		return (NULL);
	if (philo->data->stop)
		return (NULL);
	print(philo, SLEEPING);
	phi_wait(philo->data->time_to_sleep, philo);
	return ((void *)1);
}

void	*philo_routine(t_philo *philo)
{
	philo->last_meal_time = get_time(philo->data);
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
		if (phi_mimimimimi(philo) == NULL)
			return (NULL);
	}
	return (NULL);
}
