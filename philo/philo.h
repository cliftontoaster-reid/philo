/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:34:19 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/03 15:42:15 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
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

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*death_check;
}					t_simulation;

typedef struct s_arg
{
	t_philosopher	*philosopher;
	t_simulation	*simulation;
}					t_arg;

void				cleanup(t_simulation *sim, t_arg **args);

/// @brief Returns the current timestamp in milliseconds.
/// @return The current timestamp in milliseconds.
long				get_timestamp(void);

/// @brief Allocates memory for a philosopher and initializes its attributes.
/// @param id The ID of the philosopher.
/// @param simulation The simulation structure.
/// @return A pointer to the allocated philosopher structure.
t_philosopher		*create_philosopher(int id, t_simulation *simulation);

/// @brief Initializes the philosopher's attributes.
/// @param philosopher The philosopher to initialize.
void				free_philosopher(t_philosopher *philosopher);

/// @brief Allocates memory for the simulation structure and initializes its
///		attributes.
///	@param argc The number of command line arguments.
///	@param argv The command line arguments.
///	@return A pointer to the allocated simulation structure.
t_simulation		*create_simulation(int argc, char **argv);

/// @brief Frees the memory allocated for the simulation structure and its
///		attributes.
/// @param simulation The simulation structure to free.
void				free_simulation(t_simulation *simulation);

/// @brief The worker thread function for each philosopher.
/// @param arg The argument passed to the thread, containing pointers to the
///		t_philosopher and t_simulation structures.
///	@return Absolutely nothing useful.
void				*philosopher_routine(void *arg);

/// @brief Prints a message to the console with a timestamp, waiting for the
///		lock on the mutex to be released.
///	@param sim The simulation structure containing the mutex.
///	@param idx The index of the philosopher.
///	@param state The state of the philosopher.
int					phi_print(t_simulation *sim, int idx, t_state state,
						t_philosopher *philosopher);
int					usleep(long usec);

#endif
