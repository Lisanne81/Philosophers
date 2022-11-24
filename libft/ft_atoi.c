/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 14:46:00 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/24 13:28:22 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/* DESCRIPTION
**	The atoi() function converts the initial portion of the string pointed 
**	to by str to int representation.
*/

long	ft_atoi(const char *str)
{
	long	give_back;
	int		pos_neg;
	size_t	index;

	give_back = 0;
	pos_neg = 1;
	index = 0;
	while (str[index] == ' ' || str[index] == '\n' || str[index] == '\t' || \
			str[index] == '\r' || str[index] == '\v' || str[index] == '\f')
		index++;
	if (str[index] == '-')
		pos_neg = -1;
	while ((str[index] == '+' || str[index] == '-') && \
			(str[index + 1] != '+' && str[index + 1] != '-'))
		index++;
	while (str[index] && (str[index] >= '0') && (str[index] <= '9'))
	{
		give_back = give_back * 10;
		give_back += (int)str[index] - '0';
		index++;
	}
	give_back = give_back * pos_neg;
	if (give_back < -2147483648 || give_back > 2147483647)
	{
		//printf("hier\n");
		return (-1);
	}
	return (give_back);
}
