/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:22:19 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/25 10:43:56 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/// @brief Structure to hold the philosopher's data
typedef struct s_philo
{
	/// @brief The philosopher's thread ID
	int				id;
	/// @brief The philosopher's last meal time
	long			last_meal_time;
	/// @brief A pointer to the philosopher's left fork mutex
	pthread_mutex_t	*left_fork;
	/// @brief A pointer to the philosopher's right fork mutex
	pthread_mutex_t	*right_fork;
	/// @brief The number of times the philosopher has eaten
	int				meals_eaten;

	long			local_time;

	/// @brief A pointer to the philosopher's data structure, because fuck off
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	/// @brief The number of philosophers
	int				num_philos;
	/// @brief The time to eat in milliseconds
	int				time_to_eat;
	/// @brief The time to sleep in milliseconds
	int				time_to_sleep;
	/// @brief The time to die in milliseconds
	int				time_to_die;
	/// @brief The number of meals each philosopher must eat before terminating
	int				max_meals;
	/// @brief Flag to indicate simulation should stop when max meals reached
	bool			stop;
	/// @brief The current time in milliseconds
	long			time;

	/// @brief The amount of body bags needed
	int				dead_people;

	/// @brief A list of pointer to each philosopher structures
	t_philo			**philos;

	/// @brief A list of mutexes for each fork
	pthread_mutex_t	**forks;
	/// @brief A mutex for printing messages
	pthread_mutex_t	*print_mutex;
	/// @brief A mutex for modifying the current time
	pthread_mutex_t	*time_mutex;
}					t_data;

typedef enum e_philo_state
{
	/// @brief My source is that I made it the fuck up! — Max0r
	THINKING,
	/// @brief It's forking time! — Morbius
	FORK,
	/// @brief My scale is a liar! — Nikocado Avocado
	EATING,
	/// @brief Mimimimi — Martincitopants
	SLEEPING,
	/// @brief I'm on a highway to hell — AC/DC
	DEAD
}					t_philo_state;

/// @brief Initializes the philosopher data structure
/// @param argc The number of command line arguments
/// @param argv The command line arguments
/// @return A pointer to the initialized philosopher structure
t_data				*init(int argc, char **argv);
/// @brief The routine for each philosopher
/// @param philo_data A pointer to the philosopher's data structure
/// @return A pointer to the philosopher's routine result
void				*philo_routine(t_philo *philo);
/// @brief Cleans the mess made by stupid philosophers
/// @param data A pointer to the data structure
void				cleanup(t_data *data);

/// @brief A function that checks for a pulse
/// @param philo A pointer to the philosopher's structure
/// @param data A pointer to the data structure
/// @return A boolean indicating if the philosopher is dead
bool				is_dead(t_philo *philo, t_data *data);
/// @brief It's just a philosopher thing, you wouldn't understand
/// @param philo A pointer to the philosopher's structure
/// @param state The state of anxiety the philosopher is in
void				print(t_philo *philo, t_philo_state state);

/// @brief IT'S TIME, IT IS COMING
/// @param data A pointer to the data structure
/// @return The current time in milliseconds
long				get_time(t_data *data);
/// @brief You got to wait for a bit the Mc Heart attack™ is still cooking
/// @param duration The duration to wait in milliseconds
/// @param data A pointer to the data structure
/// @return The new time in milliseconds
long				phi_wait(long duration, t_philo *philo);
/// Your teacher call. Say you excel in math with 99%.
/// Now I don't have a dictionary but excel must mean STOOPID!
/// Where the other 1% go, what you eat it?
/// Now go get me a stick so I can beat you.
void				print_usage(void);

/// @brief Prototype for internal initialization of p
/// 	hilosopher structures and forks
/// @param data A pointer to the data structure
void				setup_malocs(t_data *data);

/// @brief Allocates resources for the philosopher simulation
/// @param data A pointer to the data structure
/// @return A boolean indicating success or failure
bool				allocate_resources(t_data *data);

/// @brief Prints the t_data structure in YAML format
/// @param data A pointer to the data structure
void				print_data_yaml(t_data *data);

#endif
