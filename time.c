/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 09:53:18 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/25 12:44:23 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"
#include <unistd.h>

long long	start_the_clock(void)
{
	struct timeval	time;
	long long		this_moment;

	gettimeofday(&time, NULL);
	this_moment = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

unsigned long	timer(unsigned long life_time)
{
	struct timeval	time;
	unsigned long	this_time;

	gettimeofday(&time, NULL);
	this_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - life_time;
	return (this_time);
}

void	spend_time(unsigned long current_time, unsigned long time)
{
	while ((start_the_clock() - current_time) < time)
		usleep(100);
}
