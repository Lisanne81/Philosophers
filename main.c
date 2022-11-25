/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 19:09:33 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/25 11:50:00 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	print_data(t_general *data)
{
	printf(Y20"philos\t[%d]\n"RESET, data->num_of_philos);
	printf(Y20"eat\t[%d]\n"RESET, data->eat_time);
	printf(Y20"sleep\t[%d]\n"RESET, data->sleep_time);
	printf(Y20"die\t[%d]\n"RESET, data->time_to_die);
	printf(Y20"routine\t[%d]\n"RESET, data->number_of_times_to_eat);
}

void	check_leaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_general	data;

	(void)argv;
	//ft_print_banner(1);
	if (argc > 6 || argc < 5)
		return (error_message(&data, ARG_ERROR));
	if (!memset(&data, 0, sizeof(t_general)))
		return (error_message(&data, MEMSET_FAIL));
	init_general(&data, argc, argv);
	printf(G50"in main after init\n"RESET);
	//print_data(&data);
	start_thread(data.philosopher, &data);
	free(data.philosopher);
	free(data.forks);
	atexit(check_leaks);
	return (0);
}
