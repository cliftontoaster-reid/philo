/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:59:03 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/15 16:17:55 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int	strtoint(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > (long)INT_MAX)
			return (-1);
		i++;
	}
	return ((int)result);
}

inline bool	valid_int(t_data *data)
{
	if (data->num_philos < 1 || data->num_philos > 600)
		return (false);
	if (data->time_to_die < 60 || data->time_to_die > INT_MAX)
		return (false);
	if (data->time_to_eat < 60 || data->time_to_eat > INT_MAX)
		return (false);
	if (data->time_to_sleep < 60 || data->time_to_sleep > INT_MAX)
		return (false);
	if (data->max_meals < -1)
		return (false);
	return (true);
}

void	setup_malocs(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo *) * data->num_philos);
	if (!data->philos)
		return ;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (cleanup(data));
	while (i < data->num_philos)
	{
		data->philos[i] = malloc(sizeof(t_philo));
		if (!data->philos[i])
			return (cleanup(data));
		memset(data->philos[i], 0, sizeof(t_philo));
		data->philos[i]->id = i + 1;
		data->philos[i]->data = data;
		data->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!data->forks[i])
			return (cleanup(data));
		pthread_mutex_init(data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i]->left_fork = data->forks[i];
		data->philos[i]->right_fork = data->forks[(i + 1) % data->num_philos];
		i++;
	}
	data->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!data->print_mutex)
		return (cleanup(data));
	pthread_mutex_init(data->print_mutex, NULL);
	data->time_mutex = malloc(sizeof(pthread_mutex_t));
	if (!data->time_mutex)
		return (cleanup(data));
	pthread_mutex_init(data->time_mutex, NULL);
}

t_data	*init(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data));
	data->num_philos = strtoint(argv[1]);
	data->time_to_die = strtoint(argv[2]);
	data->time_to_eat = strtoint(argv[3]);
	data->time_to_sleep = strtoint(argv[4]);
	if (argc == 6)
		data->max_meals = strtoint(argv[5]);
	else
		data->max_meals = INT_MAX;
	if (!valid_int(data))
	{
		free(data);
		return (NULL);
	}
	return (data);
}
