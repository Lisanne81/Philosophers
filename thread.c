/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 18:46:12 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/29 20:55:51 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"
#include <sys/time.h>
#include <unistd.h>

bool	whats_for_dinner(t_general *data, int index)
{
	pthread_mutex_lock(&data->philosopher[index].philo_lock);
	if (!data->philosopher[index].eat_count)
	{
		(pthread_mutex_unlock(&data->philosopher[index].philo_lock));
		return (false);
	}
	(pthread_mutex_unlock(&data->philosopher[index].philo_lock));
	return (true);
}

int 	check_vitals(t_philo *philosopher)
{
	size_t	this_time;
	size_t	time_of_death;

	pthread_mutex_lock(&philosopher->philo_lock);
	this_time = timer(philosopher->start);
	time_of_death = philosopher->last_meal + philosopher->time_to_die;
	pthread_mutex_unlock(&philosopher->philo_lock);
	if (this_time >= time_of_death)
	{
		pthread_mutex_lock(&philosopher->philo_lock);
		printer(philosopher, "is dead", "💀");
		philosopher->state_of_mind = DIED;
		pthread_mutex_unlock(&philosopher->philo_lock);
		return (DIED);
	}
	return(ALIVE);
}

int	plan_funeral(t_general *data)// void
{
	int	index;

	index = 0;
	while (data->num_of_philos > index)
	{
		pthread_mutex_lock(&data->philosopher[index].philo_lock);
		//printf("IN plan funeral[%d]\n", index + 1);
		data->philosopher[index].state_of_mind = DIED;
		pthread_mutex_unlock(&data->philosopher[index].philo_lock);
		index++;
	}
	return (0);
}

void	*check_all(void *arguments)
{
	t_general	*data;
	int			index;
	int			done_eating;
	
	data = (t_general *)arguments;
	//printf("num of philo[%d]\n", data->num_of_philos);
	while (data->start_eating > current_time())
		continue ;
	while ("the unisverse & everthing else...")
	{
		index = 0;
		done_eating = 0;
		while (data->num_of_philos > index)
		{
			if (!whats_for_dinner(data, index))
				done_eating++;
			if (check_vitals(&data->philosopher[index]) == DIED)
			{
				
				plan_funeral(data);
				//printf("is kassie wijelen\n");
				return (NULL);
			}
			index++;
		}
		if (done_eating == data->num_of_philos)
			data->all_done_eating = true;
		usleep(100);
	}
	printf(B23"LEAVE check all\n"RESET);
}

void	*daily_routine(void *arguments)
{
	t_fork	*fork;
	t_philo	*philosopher;
	
	philosopher = (t_philo *)arguments;
	fork = philosopher->fork;
	while (philosopher->start > current_time())
		continue ;
	while ("the world turns")
	{
		pthread_mutex_lock(&philosopher->data->sim_lock);
		if (philosopher->state_of_mind == DIED)
		{
			(pthread_mutex_unlock(&philosopher->data->sim_lock));
				break ;
		}
		(pthread_mutex_unlock(&philosopher->data->sim_lock));
		if (!dinner_time(fork, philosopher))
			break ;
		if (!bed_time(philosopher, philosopher->sleep_time))
			break ;
		printer(philosopher, "is thinking", "💭");
	}
	return (NULL);
}

void	start_thread(t_general *data)
{
	int	index;
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
		//spend_time(philosopher, current_time(), 1);
		index++;
	}
	if (pthread_create(check_thread, NULL, check_all, data))
		return ;
}
