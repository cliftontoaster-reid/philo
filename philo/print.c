/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:33:24 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/24 16:38:54 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_state_string(t_philo_state state)
{
	if (state == THINKING)
		return ("is thinking");
	else if (state == EATING)
		return ("is eating");
	else if (state == SLEEPING)
		return ("is sleeping");
	else if (state == DEAD)
		return ("died");
	else if (state == FORK)
		return ("has taken a fork");
	else
		return ("exploded or something, I don't know");
}

void	print(t_philo *philo, t_philo_state state)
{
	char	*str;

	pthread_mutex_lock(philo->data->print_mutex);
	if (!is_dead(philo, philo->data))
	{
		str = get_state_string(state);
		printf("%ld %d %s\n", get_time(philo->data), philo->id, str);
	}
	pthread_mutex_unlock(philo->data->print_mutex);
}

void	print_stupid(char *yellow, char *pink, char *reset)
{
	printf("Your teacher call. Say you excel in math with 99%%.\n");
	printf("Now I don't have a dictionary but excel must mean STOOPID!\n");
	printf("Where the other 1%% go, what you eat it?\n");
	printf("Now go get me a stick so I can beat you.\n\n");
	printf("%sUsage:%s ./philo <%snumber_of_philosophers%s> <%stime_to_die%s> ",
		pink, reset, yellow, reset, yellow, reset);
	printf("<%stime_to_eat%s> <%stime_to_sleep%s> [<%snumber_of_meals%s>]\n\n",
		yellow, reset, yellow, reset, yellow, reset);
	printf("%snumber_of_philosophers:%s The number of philosophers (1-600)\n",
		yellow, reset);
	printf("%stime_to_die:%s The time in milliseconds before a ", yellow,
		reset);
	printf("philosopher dies (60-INT_MAX)\n");
	printf("%stime_to_eat:%s The time in milliseconds it takes ", yellow,
		reset);
}

void	print_usage(void)
{
	char	*yellow;
	char	*cyan;
	char	*reset;
	char	*pink;

	pink = "\033[1;35m";
	yellow = "\033[1;33m";
	cyan = "\033[1;36m";
	reset = "\033[0m";
	print_stupid(yellow, pink, reset);
	printf("for a philosopher to eat (60-INT_MAX)\n");
	printf("%stime_to_sleep:%s The time in milliseconds it takes for ", yellow,
		reset);
	printf("a philosopher to sleep (60-INT_MAX)\n");
	printf("%snumber_of_meals:%s The number of meals each philosopher", yellow,
		reset);
	printf(" must eat before terminating (1-INT_MAX)\n");
	printf("%sIf number_of_meals is not provided, ", cyan);
	printf("philosophers will eat until one die.%s\n", reset);
}
