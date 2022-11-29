/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 19:09:58 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/29 21:00:04 by lhoukes       ########   odam.nl         */
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
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/time.h>
# include <fcntl.h>
# include <stdbool.h>

# define PHILO_NUM 1
# define TIME_TO_DIE 2
# define TIME_TO_EAT 3
# define TIME_TO_SLEEP 4
# define ROUNDS 5
# define SUCCES 81
# define FAIL -1
# define DELAY 150

/*------STRUCTS----------------*/

struct						s_philo;
struct						s_general;
typedef struct s_philo		t_philo;
typedef struct s_general	t_general;

typedef enum e_error_type
{
	ARG_ERROR = 1,
	MEMSET_FAIL,
	INIT_ERROR,
	MALLOC_FAIL,
	NO_ROUTINE,
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
} 	t_fork;

typedef struct s_philo
{
	int				id_philosopher;
	int				state_of_mind;
	int				left_fork;
	int				right_fork;
	long			eat_time;
	long			sleep_time;
	long			time_to_die;
	int				eat_count; //meal_size// number of rounds
	unsigned long	last_meal;
	unsigned long	start;
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
	unsigned long	start_eating;
	bool			all_done_eating;
	bool			prenounced_dead;
	t_philo			*philosopher;
	pthread_t		thread_check;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t write_lock;

}	t_general;


/*------FUNCTIONS--------------*/

int				ft_print_banner(int num);
int				check_start_input(t_general *data, int argc, char **argv);
int				check_data_input(t_general *data, int argc);
int				init_general(t_general *data, int argc, char **argv);
int				set_philos_at_dinner_table(t_general *data);
void			start_thread(t_general *data);
unsigned long	current_time(void);
long			ft_atoi(const char *str);
unsigned long	timer(unsigned long life_time);
bool			spend_time(t_philo *philosopher, unsigned long current_time, unsigned long time);
bool			bed_time(t_philo *philosopher, int sleep_time);
void			*daily_routine(void *arg);
bool			dinner_time(t_fork *fork, t_philo *philosopher);
bool				grabbed_a_fork(t_fork *fork, t_philo *philosopher);
void			printer(t_philo *philosopher, char *str, char *emoji);

/*------ERROR_CHECK------------*/
void			*protect_check(void *ptr);
void			print_data(t_general *data);
int				error_message(t_general *data, t_error_type type);

#endif