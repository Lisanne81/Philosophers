/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 09:53:18 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/12/02 10:51:27 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"
#include <unistd.h>

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	time_goes_by(t_general *data)
{
	return (current_time() - data->start_eating);
}

long	timer(long life_time)
{
	struct timeval	time;
	long			this_time;

	gettimeofday(&time, NULL);
	this_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - life_time;
	return (this_time);
}

bool	spend_time(t_philo *philosopher, unsigned long this_time, \
	unsigned long time)
{
	while ((current_time() - this_time) < time)
	{
		usleep(100);
		pthread_mutex_lock(&philosopher->philo_lock);
		if (philosopher->state_of_mind == DIED)
		{
			pthread_mutex_unlock(&philosopher->philo_lock);
			return (false);
		}
		pthread_mutex_unlock(&philosopher->philo_lock);
	}
	return (true);
}

bool	bed_time(t_philo *philosopher, int sleep_time)
{
	bool	still_alive;

	status(philosopher, "is sleeping", "💤");
	still_alive = spend_time(philosopher, current_time(), sleep_time);
	return (still_alive);
}
