/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:22:22 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/24 16:35:11 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char const *argv[])
{
	t_data		*data;
	int			i;
	pthread_t	*threads;

	if (argc < 5 || argc > 6)
	{
		print_usage();
		return (1);
	}
	data = init(argc, (char **)argv);
	if (!data)
	{
		print_usage();
		return (1);
	}
	setup_malocs(data);
	print_data_yaml(data);
	i = 0;
	threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (threads)
	{
		while (i < data->num_philos)
		{
			pthread_create(&threads[i], NULL, (void *(*)(void *))philo_routine,
				data->philos[i]);
			i++;
		}
		i = 0;
		while (i < data->num_philos)
		{
			pthread_join(threads[i], NULL);
			i++;
		}
		free(threads);
	}
	cleanup(data);
	return (threads == NULL);
}
