/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:57:30 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/15 15:04:23 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (data->forks[i] != NULL)
			pthread_mutex_destroy(data->forks[i]);
		if (data->philos[i] != NULL)
			free(data->philos[i]);
		i++;
	}
	if (data->forks != NULL)
		free(data->forks);
	if (data->philos != NULL)
		free(data->philos);
	if (data->print_mutex != NULL)
		pthread_mutex_destroy(data->print_mutex);
	if (data->time_mutex != NULL)
		pthread_mutex_destroy(data->time_mutex);
	free(data);
}
