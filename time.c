/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 09:53:18 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/29 20:55:56 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"
#include <unistd.h>


unsigned long	current_time(void)
{
	struct timeval	time;
	unsigned long	now;

	gettimeofday(&time, NULL);
	now = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (now);
}

// long long	start_the_clock(void)
// {
// 	struct timeval	time;
// 	long long		current_time;

// 	gettimeofday(&time, NULL);
// 	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
// 	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
// }

// long long	get_time(void)
// {
// 	struct timeval	time;
// 	long long		current_time;

// 	gettimeofday(&time, NULL);
// 	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
// 	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
// }

unsigned long	timer(unsigned long life_time)
{
	struct timeval	time;
	unsigned long	this_time;

	gettimeofday(&time, NULL);
	this_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - life_time;
	return (this_time);
}

bool	spend_time(t_philo *philosopher, unsigned long this_time, unsigned long time)
{
	while ((current_time() - this_time) < time)
	{
		
		usleep(100);//check of death -korte slaapjes yo moet ik al dood zijn
		pthread_mutex_lock(&philosopher->philo_lock);
		//printf("state of mind [%d]\t[%d]\n", philosopher->state_of_mind, philosopher->id_philosopher);
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

	printer(philosopher, "is sleeping", "💤");
	still_alive = spend_time(philosopher, current_time(), sleep_time);
	return (still_alive);
}
