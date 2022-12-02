/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 19:09:33 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/12/02 15:59:01 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_general	data;
	int			index;

	index = 0;
	(void)argv;
	if (argc > 6 || argc < 5)
		return (error_message(ARG_ERROR));
	if (!memset(&data, 0, sizeof(t_general)))
		return (error_message(MEMSET_FAIL));
	if (!check_input(argc, argv))
		return (error_message(INPUT_ERROR));
	if (init_general(&data, argc, argv) == SUCCES)
	{
		start_thread(&data);
		while (index < data.num_of_philos)
		{
			pthread_join(data.philosopher[index].thread, NULL);
			index++;
		}
		pthread_join(data.thread_check, NULL);
	}
	clean_up_mutexes(&data, data.num_of_philos, data.num_of_philos, true);
	free_malloced_data(&data);
	return (0);
}
