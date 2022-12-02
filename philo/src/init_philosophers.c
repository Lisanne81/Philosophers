/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philosophers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 16:02:38 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/12/01 21:35:20 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

int	set_fork_mutex(t_fork *fork, t_general *data)
{
	int	index;

	index = 0;
	fork->fork = protect_check(malloc(data->num_of_philos * \
		sizeof(pthread_mutex_t)));
	if (!fork->fork)
		return (MALLOC_FAIL);
	while (data->num_of_philos > index)
	{
		if (pthread_mutex_init(&fork->fork[index], NULL) != 0)
		{
			return (clean_up_forks(fork, index));
		}
		index++;
	}
	return (0);
}

bool	greet_every_philosopher(t_general *data, t_fork *fork)
{
	int	index;

	index = 0;
	while (data->num_of_philos > index)
	{
		data->philosopher[index].id_philosopher = index + 1;
		data->philosopher[index].state_of_mind = ALIVE;
		data->philosopher[index].left_fork = index;
		data->philosopher[index].right_fork = (index + 1) % data->num_of_philos;
		data->philosopher[index].data = data;
		data->philosopher[index].sleep_time = data->sleep_time;
		data->philosopher[index].eat_time = data->eat_time;
		data->philosopher[index].time_to_die = data->time_to_die;
		data->philosopher[index].eat_count = 0;
		data->philosopher[index].last_meal = 0;
		data->philosopher[index].start = data->start_eating;
		data->philosopher[index].fork = fork;
		if (pthread_mutex_init(&data->philosopher[index].philo_lock, NULL) != 0)
			return (clean_up_philo_mutexes(data, index));
		index++;
	}
	return (true);
}

int	set_philos_at_dinner_table(t_general *data)
{
	int		index;
	t_fork	*fork;

	index = 0;
	fork = malloc(sizeof(t_fork));
	if (!fork || set_fork_mutex(fork, data) == FAIL)
		return (FAIL);
	data->philosopher = protect_check(malloc(data->num_of_philos * \
		sizeof(t_philo)));
	if (!data->philosopher)
		return (error_message(MALLOC_FAIL));
	greet_every_philosopher(data, fork);
	return (SUCCES);
}

int	init_mutex(t_general *data)
{
	if (pthread_mutex_init(&data->sim_lock, NULL) != 0)
		return (error_message(MUTEX_ERROR));
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->sim_lock);
		return (error_message(MUTEX_ERROR));
	}
	return (0);
}

int	init_general(t_general *data, int argc, char **argv)
{
	(void)argc;
	data->num_of_philos = philo_atoi(argv[PHILO_NUM]);
	data->time_to_die = philo_atoi(argv[TIME_TO_DIE]);
	data->eat_time = philo_atoi(argv[TIME_TO_EAT]);
	data->sleep_time = philo_atoi(argv[TIME_TO_SLEEP]);
	data->delay = 200;
	data->start_eating = current_time() + data->delay;
	data->philos_eat_count = 0;
	data->all_done = false;
	if (argv[ROUNDS])
		data->number_of_times_to_eat = philo_atoi(argv[ROUNDS]);
	else
		data->number_of_times_to_eat = -1;
	init_mutex(data);
	set_philos_at_dinner_table(data);
	return (SUCCES);
}
