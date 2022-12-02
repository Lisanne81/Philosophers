/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 15:58:34 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/12/01 21:52:56 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"
#include <stdio.h>

void	*protect_check(void *ptr)
{
	if (ptr == NULL)
	{
		printf("could not malloc\n");
		return (NULL);
	}
	return (ptr);
}

int	error_message(t_error_type type)
{
	if (type == ARG_ERROR)
	{
		printf(R124"💥Not the right arguments💥\n"RESET);
		printf("Enter:"B23"\n[number of philo's]\n[time_to_die]\n");
		printf("[time_to_eat]\n[time_to_sleep]\n"RESET);
		printf(Y185"Optional:[number of times]\n"RESET);
	}
	else if (type == MEMSET_FAIL)
		printf(Y185"Not the right memset...😞"RESET);
	else if (type == INIT_ERROR)
		printf(R124"Not the right input to run program💥\n"RESET);
	else if (type == MALLOC_FAIL)
		printf(R124"Failed to allocate memory😞\n"RESET);
	else if (type == INPUT_ERROR)
		printf(R124"No valid input💥\n"RESET);
	else if (type == THREAD_ERROR)
		printf(R124"Not able to make a thread🧵\n"RESET);
	else if (type == MUTEX_ERROR)
		printf(R124"Mutex ninja 🐢 could not save the world\n"RESET);
	return (-1);
}
