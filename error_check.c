/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 15:58:34 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/26 16:21:22 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	*protect_check(void *ptr)
{
	//printf("in protect check\n");
	if (ptr == NULL)
	{
		printf("could not malloc\n");
		return (NULL);
	}
	return (ptr);
}

int	error_message(t_general *data, t_error_type type)
{
	(void)data;
	if (type == ARG_ERROR)
	{
		printf(R124"Not the right arguments\n");
		printf(B23"Enter:\n[number of philo's]\n[time_to_die]\n");
		printf("[time_to_eat]\n[time_to_sleep]\n[number of times]\n"RESET);
		return (-1);
	}
	if (type == MEMSET_FAIL)
	{
		printf(Y185"Could not allocate memory..."RESET);
		return (-1);
	}
	else if (type == INIT_ERROR)
	{
		printf(R124"Not the right input to run program\n"RESET);
		return (-1);
	}
	else if (type == MALLOC_FAIL)
	{
		printf(R124"Failed to allocate memory\n"RESET);
		return (-1);
	}
	else if (type == NO_ROUTINE)
	{
		printf(R124"No rounds to eat\n"RESET);
		return (-1);
	}
	else if (type == THREAD_ERROR)
	{
		printf(R124"Not able to make a thread\n"RESET);
		return (-1);
	}
	else if (type == MUTEX_ERROR)
	{
		printf(R124"Mutex ninja could not save the world\n"RESET);
		return (-1);
	}
	return (0);
}
