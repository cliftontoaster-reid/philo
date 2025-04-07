/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:33:55 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/07 13:33:45 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline int	ft_strtoint(const char *str)
{
	int		i;
	int		sign;
	long	result;

	if (!str)
		return (0);
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

inline long	get_timestamp(t_simulation *sim)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (sim->start_time == 0)
		sim->start_time = timestamp;
	return (timestamp - sim->start_time);
}

inline char	*get_state_str(t_simulation *sim, t_state state)
{
	if (state == THINKING)
		return ("is thinking");
	if (state == EATING)
		return ("is eating");
	if (state == SLEEPING)
		return ("is sleeping");
	if (state == TAKING_FORK)
		return ("has taken a fork");
	if (state == DIED)
	{
		sim->finished_philosophers++;
		return ("died");
	}
	return (NULL);
}

int	phi_print(t_simulation *sim, int idx, t_state state, t_philosopher *phi)
{
	char	*state_str;

	pthread_mutex_lock(sim->print_mutex);
	if (sim->finished_philosophers > 0 && state != DIED)
	{
		pthread_mutex_unlock(sim->print_mutex);
		pthread_mutex_unlock(phi->left_fork);
		pthread_mutex_unlock(phi->right_fork);
		return (1);
	}
	state_str = get_state_str(sim, state);
	if (!state_str && sim->finished_philosophers == 0)
	{
		return (0);
	}
	printf("%ld %d %s\n", get_timestamp(sim), idx + 1, state_str);
	pthread_mutex_unlock(sim->print_mutex);
	return (state == DIED || sim->finished_philosophers > 0);
}
