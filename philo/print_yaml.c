/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_yaml.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:01:19 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/26 15:04:58 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> // Include stdio.h for stderr

static void	print_data_overview(t_data *d)
{
	fprintf(stderr, "- data:\n");
	fprintf(stderr, "    num_philos: %d\n", d->num_philos);
	fprintf(stderr, "    time_to_eat: %d\n", d->time_to_eat);
	fprintf(stderr, "    time_to_sleep: %d\n", d->time_to_sleep);
	fprintf(stderr, "    time_to_die: %d\n", d->time_to_die);
	fprintf(stderr, "    max_meals: %d\n", d->max_meals);
	fprintf(stderr, "    time: %ld\n", d->time);
	fprintf(stderr, "    dead_people: %d\n", d->dead_people);
	if (d->stop)
		fprintf(stderr, "  stop: true\n");
	else
		fprintf(stderr, "  stop: false\n");
}

static void	print_philos_list(t_data *d)
{
	int		i;
	t_philo	*p;
	int		idx;

	fprintf(stderr, "  philos:\n");
	i = 0;
	while (i < d->num_philos)
	{
		p = d->philos[i];
		idx = p->id - 1;
		fprintf(stderr, "      - id: %d\n", p->id);
		fprintf(stderr, "        last_meal_time: %ld\n", p->last_meal_time);
		fprintf(stderr, "        meals_eaten: %d\n", p->meals_eaten);
		fprintf(stderr, "        left_fork: fork%d\n", idx);
		fprintf(stderr, "        right_fork: fork%d\n", (idx + 1)
			% d->num_philos);
		++i;
	}
}

static void	print_forks_list(t_data *d)
{
	int	i;

	fprintf(stderr, "  forks:\n");
	i = 0;
	while (i < d->num_philos)
	{
		fprintf(stderr, "    - fork%d\n", i);
		++i;
	}
}

static void	print_addresses(t_data *d)
{
	int	i;

	fprintf(stderr, "  addresses:\n");
	i = 0;
	while (i < d->num_philos)
	{
		fprintf(stderr, "    fork%d: %p\n", i, (void *)d->forks[i]);
		++i;
	}
	fprintf(stderr, "    print_mutex: %p\n", (void *)d->print_mutex);
	fprintf(stderr, "    time_mutex: %p\n", (void *)d->time_mutex);
}

void	print_data_yaml(t_data *d)
{
	if (true)
		return ;
	pthread_mutex_lock(d->print_mutex);
	pthread_mutex_lock(d->time_mutex);
	print_data_overview(d);
	print_philos_list(d);
	print_forks_list(d);
	fprintf(stderr, "  print_mutex: print_mutex\n");
	fprintf(stderr, "  time_mutex: time_mutex\n");
	print_addresses(d);
	pthread_mutex_unlock(d->time_mutex);
	pthread_mutex_unlock(d->print_mutex);
	fprintf(stderr, "\n");
}
