/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wait_your_turn.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/26 15:33:42 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/12/02 13:42:06 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"
#include <unistd.h>

bool	wait_your_turn(t_philo *philosopher, long wait_time)
{
	long	wait_start;
	long	wait_end;

	wait_start = time_goes_by(philosopher->data);
	wait_end = wait_start + wait_time;
	while (true)
	{
		if (time_goes_by(philosopher->data) >= wait_end)
			return (true);
		usleep(250);
	}
}

bool	think_time(t_philo *philosopher)
{
	long	time_to_think;
	long	wait_start;
	long	time_last_meal;

	wait_start = time_goes_by(philosopher->data);
	pthread_mutex_lock(&philosopher->philo_lock);
	time_last_meal = philosopher->last_meal;
	pthread_mutex_unlock(&philosopher->philo_lock);
	time_to_think = (philosopher->time_to_die
			- (wait_start - time_last_meal)
			- philosopher->eat_time) / 2;
	if (time_to_think > 1000)
		time_to_think = 500;
	if (time_to_think < 0)
		time_to_think = 0;
	if (!wait_your_turn(philosopher, time_to_think))
		return (false);
	return (true);
}

bool	this_is_the_end(t_general *data)
{
	bool	stop_the_show;

	stop_the_show = true;
	pthread_mutex_lock(&data->sim_lock);
	if (data->philos_eat_count == data->num_of_philos || \
		data->philosopher->state_of_mind == DIED)
		data->all_done = true;
	stop_the_show = data->all_done;
	pthread_mutex_unlock(&data->sim_lock);
	plan_funeral(data);
	return (stop_the_show);
}
