/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   status_report.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 19:54:34 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/12/02 15:59:15 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"
#include <stdio.h>

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	counter;

	counter = 0;
	while ((s1[counter] != '\0' || s2[counter] != '\0') && counter < n)
	{
		if (s1[counter] != s2[counter])
		{
			return ((unsigned char)s1[counter] - (unsigned char)s2[counter]);
		}
		counter++;
	}
	return (0);
}

void	status(t_philo *philosopher, char *str, char *emoji)
{
	pthread_mutex_lock(&philosopher->data->write_lock);
	if (philosopher->state_of_mind == ALIVE || !ft_strncmp(str, "died", 4))
	{
		printf(Y185"%-5lu"RESET " Philosopher %-5d %-20s %s\n",
			timer(philosopher->start), philosopher->id_philosopher, str, emoji);
		pthread_mutex_unlock(&philosopher->data->write_lock);
	}
	pthread_mutex_unlock(&philosopher->data->write_lock);
}
