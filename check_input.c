/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 09:41:50 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/25 10:07:52 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

int	check_data_input(t_general *data, int argc)
{
	printf("argc[%d]\n", argc);
	if (data->num_of_philos < 1 || data->num_of_philos > 200)
		return (error_message(data, INIT_ERROR));
	if (data->eat_time < 0 || data->sleep_time < 0 || data->time_to_die < 0)
		return (error_message(data, INIT_ERROR));
	if (argc == 6 && data->number_of_times_to_eat < 1 && \
		data->number_of_times_to_eat != -1)
		return (error_message(data, NO_ROUTINE));
	return (0);
}

int	check_start_input(t_general *data, int argc, char **argv)
{
	int	index;

	index = 1;
	printf("argc[%d]\n", argc);
	while (index < argc - 1)
	{
		printf("argv[%s][%ld]\n", argv[index], ft_atoi(argv[index]));
		if (ft_atoi(argv[index]) == -1)
		{
			printf("in loop to check\n");
			return (error_message(data, INIT_ERROR));
		}
		index++;
	}
	return (0);
}