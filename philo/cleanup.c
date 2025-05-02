/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:57:30 by lfiorell          #+#    #+#             */
/*   Updated: 2025/05/02 12:36:15 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	free_philo(t_data *data, int i)
{
	if (data->forks[i] != NULL)
	{
		pthread_mutex_destroy(data->forks[i]);
		free(data->forks[i]);
	}
	if (data->philos[i] != NULL)
		free(data->philos[i]);
	i++;
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
		free_philo(data, i++);
	if (data->forks != NULL)
		free(data->forks);
	if (data->philos != NULL)
		free(data->philos);
	if (data->print_mutex != NULL)
	{
		pthread_mutex_destroy(data->print_mutex);
		free(data->print_mutex);
	}
	if (data->time_mutex != NULL)
	{
		pthread_mutex_destroy(data->time_mutex);
		free(data->time_mutex);
	}
	free(data);
}
