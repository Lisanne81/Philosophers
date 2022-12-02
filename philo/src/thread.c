/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 18:46:12 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/12/02 16:07:05 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int	plan_funeral(t_general *data)
{
	int	index;

	index = 0;
	while (data->num_of_philos > index)
	{
		pthread_mutex_lock(&data->philosopher[index].philo_lock);
		data->philosopher[index].state_of_mind = DIED;
		pthread_mutex_unlock(&data->philosopher[index].philo_lock);
		index++;
	}
	return (0);
}

int	check_vitals(t_philo *philosopher)
{
	long	this_time;
	long	time_of_death;

	pthread_mutex_lock(&philosopher->philo_lock);
	this_time = timer(philosopher->start);
	time_of_death = philosopher->last_meal + philosopher->time_to_die;
	pthread_mutex_unlock(&philosopher->philo_lock);
	if (this_time >= time_of_death)
	{
		pthread_mutex_lock(&philosopher->philo_lock);
		status(philosopher, "died", "💀");
		philosopher->state_of_mind = DIED;
		pthread_mutex_unlock(&philosopher->philo_lock);
		return (DIED);
	}
	return (ALIVE);
}

void	*check_all(void *arguments)
{
	t_general	*data;
	int			index;

	data = (t_general *)arguments;
	while (data->start_eating > current_time())
		continue ;
	while ("the unisverse & everthing else...")
	{
		if (data->num_of_philos == data->philos_eat_count)
		{
			this_is_the_end(data);
			return (NULL);
		}
		index = 0;
		while (data->num_of_philos > index)
		{
			if (check_vitals(&data->philosopher[index]) == DIED)
			{
				plan_funeral(data);
				return (NULL);
			}
			index++;
		}
		usleep(100);
	}
}

void	*daily_routine(void *arguments)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arguments;
	while (philosopher->start > current_time())
		continue ;
	if (philosopher->id_philosopher % 2 == 1)
		usleep(200);
	while ("the world turns")
	{
		if (!dinner_time(philosopher->fork, philosopher))
			break ;
		if (!bed_time(philosopher, philosopher->sleep_time))
			break ;
		if (!think_time(philosopher))
			break ;
		status(philosopher, "is thinking", "💭");
	}
	return (NULL);
}

void	start_thread(t_general *data)
{
	int			index;
	pthread_t	*thread;
	pthread_t	*check_thread;
	t_philo		*philosopher;

	index = 0;
	check_thread = &data->thread_check;
	while (data->num_of_philos > index)
	{
		philosopher = &data->philosopher[index];
		thread = &data->philosopher[index].thread;
		if (pthread_create(thread, NULL, daily_routine, philosopher))
			return ;
		index++;
	}
	usleep(100);
	if (pthread_create(check_thread, NULL, check_all, data))
		return ;
	pthread_mutex_lock(&data->write_lock);
	data->all_done = true;
	pthread_mutex_unlock(&data->write_lock);
	return ;
}
