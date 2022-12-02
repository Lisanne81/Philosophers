/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 09:41:50 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/12/01 22:12:45 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

int	philo_atoi(char *input)
{
	unsigned long long int	number;
	int						index;

	index = 0;
	number = 0;
	while (input[index] && (input[index] >= '0' && input[index] <= '9'))
	{
		number = number * 10 + (input[index] - '0');
		index++;
	}
	if (number > 2147483647)
		return (-1);
	return ((int)number);
}

static bool	is_only_digit(char *input)
{
	int	index;

	index = 0;
	while (input[index])
	{
		if (input[index] < '0' || input[index] > '9')
		{
			return (false);
		}
		index++;
	}
	return (true);
}

bool	check_input(int argc, char **argv)
{
	int	index;
	int	convert_input;

	index = 1;
	while (argc > index)
	{
		if (!is_only_digit(argv[index]))
			return (false);
		convert_input = philo_atoi(argv[index]);
		if (index == PHILO_NUM && (convert_input <= 0 || convert_input > 200))
			return (false);
		if (index != 1 && convert_input < 0)
			return (false);
		if (index == ROUNDS && convert_input <= 0)
			return (false);
		index++;
	}
	return (true);
}
