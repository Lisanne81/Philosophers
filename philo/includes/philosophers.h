/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 19:09:58 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/12/06 16:05:46 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*------COLORS--------------*/
# define R124 "\e[38;5;196m"
# define O17 "\e[38;5;202m"
# define O18 "\e[38;5;209m"
# define Y19 "\e[38;5;214m"
# define Y20 "\e[38;5;216m"
# define P21 "\e[38;5;21m"
# define G22 "\e[38;5;22m"
# define B23 "\e[38;5;23m"
# define Y185 "\e[38;5;185m"
# define G40 "\e[38;5;40m"
# define G41 "\e[38;5;41m"
# define G42 "\e[38;5;42m"
# define G43 "\e[38;5;43m"
# define G46 "\e[38;5;46m"
# define G47 "\e[38;5;47m"
# define G48 "\e[38;5;48m"
# define G49 "\e[38;5;49m"
# define G50 "\e[38;5;50m"
# define RESET "\e[0m"

/*------LIBRARIES--------------*/
//# include "../libft/libft.h"
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

# define PHILO_NUM 1
# define TIME_TO_DIE 2
# define TIME_TO_EAT 3
# define TIME_TO_SLEEP 4
# define ROUNDS 5
# define SUCCES 81
# define FAIL -1
# define DELAY 200

/*------STRUCTS----------------*/

struct						s_philo;
struct						s_general;
struct						s_fork;
typedef struct s_fork		t_fork;
typedef struct s_philo		t_philo;
typedef struct s_general	t_general;

typedef enum e_error_type
{
	ARG_ERROR = 1,
	MEMSET_FAIL,
	INIT_ERROR,
	MALLOC_FAIL,
	INPUT_ERROR,
	MUTEX_ERROR,
	THREAD_ERROR,
	NONE
}	t_error_type;

typedef enum e_status
{
	GRABBED_FORK = 10,
	EAT,
	SLEEP,
	THINK,
	DONE,
	ALIVE,
	DIED,
}	t_status;

typedef struct s_fork
{
	pthread_mutex_t	*fork;
}	t_fork;

typedef struct s_philo
{
	int				id_philosopher;
	int				state_of_mind;
	int				left_fork;
	int				right_fork;
	long			eat_time;
	long			sleep_time;
	long			time_to_die;
	int				eat_count;
	long			last_meal;
	long			start;
	t_general		*data;
	t_fork			*fork;
	pthread_t		thread;
	pthread_mutex_t	philo_lock;

}	t_philo;
typedef struct s_general
{
	int				num_of_philos;
	int				eat_time;
	int				sleep_time;
	long			time_to_die;
	int				number_of_times_to_eat;
	int				philos_eat_count;
	long			start_eating;
	long			delay;
	bool			all_done;
	t_philo			*philosopher;
	pthread_t		thread_check;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t	write_lock;
}	t_general;

/*------FUNCTIONS--------------*/

int				philo_atoi(char *input);
int				init_general(t_general *data, int argc, char **argv);
int				error_message(t_error_type type);
int				set_philos_at_dinner_table(t_general *data);
void			start_thread(t_general *data);
void			*daily_routine(void *arg);
void			free_malloced_data(t_general *data);
void			status(t_philo *philosopher, char *str, char *emoji);
void			*protect_check(void *ptr);
long			timer(long life_time);
long			current_time(void);
long			time_goes_by(t_general *data);
int				plan_funeral(t_general *data);
bool			check_input(int argc, char **argv);
bool			greet_every_philosopher(t_general *data, t_fork *fork);
bool			bed_time(t_philo *philosopher, int sleep_time);
bool			wait_your_turn(t_philo *philosopher, long wait_time);
bool			this_is_the_end(t_general *data);
bool			think_time(t_philo *philosopher);
bool			dinner_time(t_fork *fork, t_philo *philosopher);
bool			grabbed_a_fork(t_fork *fork, t_philo *philosopher);
bool			we_are_full(t_general *data);
bool			this_is_the_end(t_general *data);
bool			spend_time(t_philo *philosopher, \
					unsigned long current_time, unsigned long time);
bool			clean_up_philo_mutexes(t_general *data, int index);
bool			clean_up_forks(t_fork *fork, int index);
bool			clean_up_mutexes(t_general *data, int fork_mutexes, \
					int philo_mutexes, bool data_locks_created);
#endif