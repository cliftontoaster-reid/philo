/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:22:22 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/24 15:31:07 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char const *argv[])
{
	t_data	*data;

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
	cleanup(data);
	return (0);
}

void	print_data_yaml(t_data *d)
{
	int		i;
	t_philo	*p;
	int		idx;

	printf("data:\n");
	printf("  num_philos: %d\n", d->num_philos);
	printf("  time_to_eat: %d\n", d->time_to_eat);
	printf("  time_to_sleep: %d\n", d->time_to_sleep);
	printf("  time_to_die: %d\n", d->time_to_die);
	printf("  max_meals: %d\n", d->max_meals);
	printf("  time: %ld\n", d->time);
	printf("  dead_people: %d\n", d->dead_people);
	printf("  philos:\n");
	i = -1;
	while (++i < d->num_philos)
	{
		p = d->philos[i];
		idx = p->id - 1;
		printf("    - id: %d\n", p->id);
		printf("      last_meal_time: %ld\n", p->last_meal_time);
		printf("      meals_eaten: %d\n", p->meals_eaten);
		printf("      left_fork: fork%d\n", idx);
		printf("      right_fork: fork%d\n", (idx + 1) % d->num_philos);
	}
	printf("  forks:\n");
	i = -1;
	while (++i < d->num_philos)
		printf("    - fork%d\n", i);
	printf("  print_mutex: print_mutex\n");
	printf("  time_mutex: time_mutex\n");
	printf("addresses:\n");
	i = -1;
	while (++i < d->num_philos)
		printf("  fork%d: %p\n", i, (void *)d->forks[i]);
	printf("  print_mutex: %p\n", (void *)d->print_mutex);
	printf("  time_mutex: %p\n", (void *)d->time_mutex);
}
