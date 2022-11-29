/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 19:09:33 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/29 20:25:25 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	print_data(t_general *data)
{
	printf(Y20"philos\t[%d]\n"RESET, data->num_of_philos);
	printf(Y20"eat\t[%d]\n"RESET, data->eat_time);
	printf(Y20"sleep\t[%d]\n"RESET, data->sleep_time);
	printf(Y20"die\t[%ld]\n"RESET, data->time_to_die);
	printf(Y20"routine\t[%d]\n"RESET, data->number_of_times_to_eat);
}

void	check_leaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_general	data;
	int			index;

	index = 0;
	(void)argv;

	if (argc > 6 || argc < 5)
		return (error_message(&data, ARG_ERROR));
	if (!memset(&data, 0, sizeof(t_general)))
		return (error_message(&data, MEMSET_FAIL));
	//init_general(&data, argc, argv);
	printf("back in main\n");
	//start_thread(&data);
	if (init_general(&data, argc, argv) == SUCCES)
	{
		//printf("before start thread\n");
		start_thread(&data);
		while (index < data.num_of_philos)
		{
			if (pthread_join(data.philosopher[index].thread, NULL))
				return (FAIL);
			index++;
		}
		if (pthread_join(data.thread_check, NULL))
			return (FAIL);
	}

	free(data.philosopher);
	//atexit(check_leaks);
	return (0);
}
