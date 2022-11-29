/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philosophers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 16:02:38 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/29 20:18:24 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

// int	set_mutex_philo(t_general *data)
// {
// 	int	index;

// 	// index = 0;
// 	// while (data->num_of_philos > index)
// 	// {
// 	// 	printf("in init5\n");
// 	// 	if (pthread_mutex_init(&data->philosopher[index].lock, 0) != 0)
// 	// 		return (index);
// 	// 	index++;
// 	// }
// 	index = 0;
// 	while (data->num_of_philos > index)
// 	{
// 		printf("in init6\n");
// 		data->philosopher[index].death_of_philo = &data->death_of_philo;
// 		data->philosopher[index].count_meals = &data->count_meals;
// 		data->philosopher[index].meal_time = &data->meal_time;
// 		index++;
// 	}
// 	return (SUCCES);
// }

int	set_fork_mutex(t_fork *fork, t_general *data)
{
	int	index;

	index = 0;
	fork->fork = protect_check(malloc(data->num_of_philos * \
		sizeof(pthread_mutex_t)));
	if (!fork->fork)
		return (FAIL);
	while (data->num_of_philos > index)
	{

		if (pthread_mutex_init(&fork->fork[index], NULL) != 0)
		{
			return (FAIL);
		}
		index++;
	}
	//set_mutex_philo(data);
	return (0);
}
		//printf("set the table for philo[%d]\n", index);
		//printf("left_fork[%d]\n", data->philosopher[index].left_fork);
		//printf(G42"right_fork[%d]\n"RESET, data->philosopher[index].right_fork);

int	set_philos_at_dinner_table(t_general *data)
{
	int		index;
	t_fork	*fork;

	index = 0;
	fork = malloc(sizeof(t_fork));
	if (!fork || set_fork_mutex(fork, data) == FAIL)
		return (FAIL);
	data->philosopher = protect_check(malloc(data->num_of_philos * \
		sizeof(t_philo)));
	if (!data->philosopher)
		return (error_message(data, MALLOC_FAIL));
	while (data->num_of_philos > index)
	{
		data->philosopher[index].id_philosopher = index + 1;
		data->philosopher[index].state_of_mind = ALIVE;
		data->philosopher[index].left_fork = index;
		data->philosopher[index].right_fork = (index + 1) % data->num_of_philos;
		data->philosopher[index].data = data;
		data->philosopher[index].sleep_time = data->sleep_time;
		data->philosopher[index].eat_time = data->eat_time;
		data->philosopher[index].time_to_die = data->time_to_die;
		data->philosopher[index].eat_count = data->number_of_times_to_eat;
		data->philosopher[index].last_meal = 0;
		data->philosopher[index].start = data->start_eating;
		data->philosopher[index].fork = fork;
		if (pthread_mutex_init(&data->philosopher[index].philo_lock, NULL) != 0)
			return (-1);
		index++;
	}
	return (SUCCES);
}

int	init_mutex(t_general *data)
{
	if (pthread_mutex_init(&data->sim_lock, NULL) != 0 || \
		pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (error_message(data, MUTEX_ERROR));
	return (0);
}

int	init_general(t_general *data, int argc, char **argv)
{

	check_start_input(data, argc, argv);
	data->num_of_philos = ft_atoi(argv[PHILO_NUM]);
	data->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	data->eat_time = ft_atoi(argv[TIME_TO_EAT]);
	data->sleep_time = ft_atoi(argv[TIME_TO_SLEEP]);
	data->start_eating = current_time() + DELAY;
	data->all_done_eating = false;
	data->prenounced_dead = false;
	if (argv[ROUNDS])
		data->number_of_times_to_eat = ft_atoi(argv[ROUNDS]);
	else
		data->number_of_times_to_eat = -1;
	init_mutex(data);
	set_philos_at_dinner_table(data);
	return (SUCCES);
}
