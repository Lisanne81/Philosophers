/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philosophers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 16:02:38 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/24 18:59:28 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

int	set_mutex_philo(t_general *data)
{
	int	index;

	index = 0;
	while (data->num_of_philos > index)
	{
		if (pthread_mutex_init(&data->philosopher[index].lock, 0) != 0)
			return (index);
		index++;
	}
	return (0);
}

int	set_mutex(t_general *data)
{
	int	index;

	index = 0;
	// 	if (pthread_mutex_init(&data->log_info, NULL))
	// 	return (1);
	// if (pthread_mutex_init(&data->set_lock, 0))
	// 	return (1);
	data->forks = protect_check(malloc(data->num_of_philos * \
		sizeof(pthread_mutex_t)));
	if (!data->forks)
		return (0);
	while (data->num_of_philos > index)
	{
		if (pthread_mutex_init(&data->forks[index], 0) != 0)
			return (index);
		index++;
	}
	if (set_mutex_philo(data))
		return (1);
	return (0);
}

int	set_philos_at_dinner_table(t_general *data)
{
	int	index;

	index = 0;
	data->philosopher = protect_check(malloc(data->num_of_philos * \
		sizeof(t_general)));
	if (!data->philosopher)
		return (error_message(data, MALLOC_FAIL));
	while (data->num_of_philos > index)
	{
		printf("set the table for philo[%d]\n", index);
		data->philosopher[index].data = data;
		data->philosopher[index].id_philosopher = index;
		data->philosopher[index].eat_count = 0;
		data->philosopher[index].last_meal = 0;
		data->philosopher[index].left_fork = index;
		data->philosopher[index].right_fork = (index + 1) % data->num_of_philos;
		printf("left_fork[%d]\n", data->philosopher[index].left_fork);
		printf(G42"right_fork[%d]\n"RESET, data->philosopher[index].right_fork);
		index++;
	}
	if (set_mutex(data))
		return (1);
	return (0);
}

int	check_data_input(t_general *data, int argc)
{
	printf("argc[%d]\n", argc);
	if (data->num_of_philos < 1 || data->num_of_philos > 200)
		return (error_message(data, INIT_ERROR));
	if (data->eat_time < 0 || data->sleep_time < 0 || data->time_to_die < 0)
		return (error_message(data, INIT_ERROR));
	if (argc == 6 && data->number_of_times < 1 && data->number_of_times != -1)
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

int	init_general(t_general *data, int argc, char **argv)
{
	check_start_input(data, argc, argv);
	data->num_of_philos = ft_atoi(argv[1]);
	data->eat_time = ft_atoi(argv[2]);
	data->sleep_time = ft_atoi(argv[3]);
	data->time_to_die = ft_atoi(argv[4]);
	data->start_eating = 0;
	data->done_eating = 0;
	if (argc == 6)
		data->number_of_times = ft_atoi(argv[5]);
	else
		data->number_of_times = -1;
	if (check_data_input(data, argc))
		return (1);
	if (set_philos_at_dinner_table(data))
		return (1);
	return (0);
}
