/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:26:52 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/03 11:50:05 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

static int	ft_strtoint(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result * sign > INT_MAX || result * sign < INT_MIN)
		return (-1);
	return ((int)(result * sign));
}

t_simulation	*create_simulation(int argc, char **argv)
{
	t_simulation	*sim;

	sim = (t_simulation *)malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	memset(sim, 0, sizeof(t_simulation));
	sim->num_philosophers = ft_strtoint(argv[1]);
	sim->time_to_die = ft_strtoint(argv[2]);
	sim->time_to_eat = ft_strtoint(argv[3]);
	sim->time_to_sleep = ft_strtoint(argv[4]);
	if (argc == 6)
		sim->eat_limit = ft_strtoint(argv[5]);
	else
		sim->eat_limit = INT_MAX;
	if (sim->num_philosophers <= 0 || sim->time_to_die <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0
		|| sim->eat_limit <= 0)
	{
		free(sim);
		return (NULL);
	}
	return (sim);
}
