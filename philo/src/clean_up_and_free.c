/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up_and_free.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 19:09:13 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/12/06 15:18:59 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

bool	clean_up_philo_mutexes(t_general *data, int index)
{
	bool	destroyed;

	destroyed = true;
	while (index > 0)
	{
		index--;
		if (pthread_mutex_destroy(&data->philosopher[index].philo_lock) != 0)
			destroyed = false;
	}
	return (destroyed);
}

bool	clean_up_forks(t_fork *fork, int index)
{
	bool	destroyed;

	destroyed = true;
	while (index > 0)
	{
		index--;
		if (pthread_mutex_destroy(&fork->fork[index]) != 0)
			destroyed = false;
	}
	if (fork->fork)
		free (fork->fork);
	if (fork)
		free(fork);
	return (destroyed);
}

bool	clean_up_mutexes(t_general *data, int fork_mutexes, int philo_mutexes,
	bool data_locks_created)
{
	bool	destroyed;

	destroyed = true;
	if (!clean_up_forks(data->philosopher->fork, fork_mutexes))
		destroyed = false;
	if (!clean_up_philo_mutexes(data, philo_mutexes))
		destroyed = false;
	if (data_locks_created)
	{
		if (pthread_mutex_destroy(&data->sim_lock) != 0)
			destroyed = false;
		if (pthread_mutex_destroy(&data->write_lock) != 0)
			destroyed = false;
	}
	return (destroyed);
}

void	free_malloced_data(t_general *data)
{
	if (!data)
		return ;
	if (data->philosopher)
		free(data->philosopher);
}
