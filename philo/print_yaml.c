/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_yaml.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:01:19 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/24 16:24:13 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_data_overview(t_data *d)
{
	printf("data:\n");
	printf("  num_philos: %d\n", d->num_philos);
	printf("  time_to_eat: %d\n", d->time_to_eat);
	printf("  time_to_sleep: %d\n", d->time_to_sleep);
	printf("  time_to_die: %d\n", d->time_to_die);
	printf("  max_meals: %d\n", d->max_meals);
	printf("  time: %ld\n", d->time);
	printf("  dead_people: %d\n", d->dead_people);
}

static void	print_philos_list(t_data *d)
{
	int		i;
	t_philo	*p;
	int		idx;

	printf("  philos:\n");
	i = 0;
	while (i < d->num_philos)
	{
		p = d->philos[i];
		idx = p->id - 1;
		printf("    - id: %d\n", p->id);
		printf("      last_meal_time: %ld\n", p->last_meal_time);
		printf("      meals_eaten: %d\n", p->meals_eaten);
		printf("      left_fork: fork%d\n", idx);
		printf("      right_fork: fork%d\n", (idx + 1) % d->num_philos);
		++i;
	}
}

static void	print_forks_list(t_data *d)
{
	int	i;

	printf("  forks:\n");
	i = 0;
	while (i < d->num_philos)
	{
		printf("    - fork%d\n", i);
		++i;
	}
}

static void	print_addresses(t_data *d)
{
	int	i;

	printf("addresses:\n");
	i = 0;
	while (i < d->num_philos)
	{
		printf("  fork%d: %p\n", i, (void *)d->forks[i]);
		++i;
	}
	printf("  print_mutex: %p\n", (void *)d->print_mutex);
	printf("  time_mutex: %p\n", (void *)d->time_mutex);
}

void	print_data_yaml(t_data *d)
{
	print_data_overview(d);
	print_philos_list(d);
	print_forks_list(d);
	printf("  print_mutex: print_mutex\n");
	printf("  time_mutex: time_mutex\n");
	print_addresses(d);
}
