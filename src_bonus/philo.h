/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:34:31 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/07 13:06:13 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	TAKING_FORK,
	DIED
}					t_state;

typedef struct s_philosopher
{
	int				id;
	long			last_nom;
	int				eat_count;
	int				eat_limit;
	int				time_to_think;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;

	pthread_t		thread;
}					t_philosopher;

typedef struct s_simulation
{
	int				num_philosophers;
	int				time_to_think;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				eat_limit;

	t_philosopher	**philosophers;
	int				finished_philosophers;
	sem_t			forks;
	sem_t			print_mutex;
}					t_simulation;

typedef struct s_arg
{
	t_philosopher	*philosopher;
	t_simulation	*simulation;
}					t_arg;

int					setup_malocs(t_simulation *sim);
void				cleanup(t_simulation *sim, t_arg **args);
int					phi_print(t_simulation *sim, int idx, t_state state);
t_philosopher		*create_philosopher(int id, t_simulation *sim);
t_simulation		*create_simulation(int argc, char **argv);
long				get_timestamp(void);
int					usleep(long usec);
int					ft_strtoint(const char *str);
void				*philosopher_routine(void *arg);

#endif
