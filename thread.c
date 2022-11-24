/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 18:46:12 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/24 19:15:39 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"
#include <sys/time.h>

int	start_the_clock(void)
{
	struct timeval	time;
	long long		this_moment;
	
	gettimeofday(&time, NULL);
	this_moment = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	start_thread(t_philo *philosopher, t_general *data)
{
	int	index;
	
	(void)philosopher;
	index = 0;
	data->start_eating = start_the_clock();
	printf(P21"time is[%d]\n", data->start_eating);
	return (0);
}
