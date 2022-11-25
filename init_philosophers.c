/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philosophers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 16:02:38 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/25 12:06:53 by lhoukes       ########   odam.nl         */
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
		//printf("set the table for philo[%d]\n", index);
		data->philosopher[index].data = data;
		data->philosopher[index].id_philosopher = index;
		data->philosopher[index].eat_count = 0;
		data->philosopher[index].last_meal = 0;
		data->philosopher[index].left_fork = index;
		data->philosopher[index].right_fork = (index + 1) % data->num_of_philos;
		//printf("left_fork[%d]\n", data->philosopher[index].left_fork);
		//printf(G42"right_fork[%d]\n"RESET, data->philosopher[index].right_fork);
		index++;
	}
	if (set_mutex(data))
		return (1);
	return (0);
}

int	init_general(t_general *data, int argc, char **argv)
{
	check_start_input(data, argc, argv);
	data->num_of_philos = ft_atoi(argv[1]);
	data->eat_time = ft_atoi(argv[2]);
	data->sleep_time = ft_atoi(argv[3]);
	data->time_to_die = ft_atoi(argv[4]);
	data->start_eating = start_the_clock();
	data->done_eating = 0;
	if (argc == 6)
		data->number_of_times_to_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_to_eat = -1;
	if (pthread_mutex_init(&data->log_info, NULL) != 0)
		return (MUTEX_ERROR);
	if (pthread_mutex_init(&data->set_lock, 0) != 0)
		return (MUTEX_ERROR);
	if (check_data_input(data, argc))
		return (INIT_ERROR);
	if (set_philos_at_dinner_table(data))
		return (INIT_ERROR);
	return (0);
}
