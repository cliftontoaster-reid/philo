/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creid <creid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:22:22 by lfiorell          #+#    #+#             */
/*   Updated: 2025/05/12 15:50:27 by creid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline t_data	*init_simulation(int argc, char const *argv[])
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		print_usage();
		return (NULL);
	}
	data = init(argc, (char **)argv);
	if (!data)
	{
		print_usage();
		return (NULL);
	}
	setup_malocs(data);
	print_data_yaml(data);
	return (data);
}

static inline pthread_t	*spawn_philosophers(t_data *data)
{
	int			i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!threads)
		return (NULL);
	i = 0;
	while (i < data->num_philos)
	{
		if (i % 2 == 0)
			pthread_create(&threads[i], NULL, (void *(*)(void *))philo_routine,
				data->philos[i]);
		i++;
	}
	usleep(100);
	i = 0;
	while (i < data->num_philos)
	{
		if (i % 2 == 1)
			pthread_create(&threads[i], NULL, (void *(*)(void *))philo_routine,
				data->philos[i]);
		i++;
	}
	return (threads);
}

static inline void	join_and_free(pthread_t *threads, t_data *data)
{
	int	i;

	if (!threads)
		return ;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
}

static inline void	wait_n_print(t_data *data)
{
	bool	owo;

	while (true)
	{
		pthread_mutex_lock(data->print_mutex);
		owo = (data->dead_people > 0 || data->stop);
		pthread_mutex_unlock(data->print_mutex);
		if (owo)
			break ;
		usleep(100);
	}
	print_data_yaml(data);
}

int	main(int argc, char const *argv[])
{
	t_data		*data;
	pthread_t	*threads;

	data = init_simulation(argc, argv);
	if (!data)
		return (1);
	if (data->num_philos == 1)
	{
		print(data->philos[0], FORK);
		usleep(data->time_to_die * 1000);
		print(data->philos[0], DEAD);
		cleanup(data);
		return (0);
	}
	threads = spawn_philosophers(data);
	join_and_free(threads, data);
	wait_n_print(data);
	cleanup(data);
	return (threads == NULL);
}
