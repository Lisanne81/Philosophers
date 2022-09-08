/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/22 14:24:26 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/08/16 20:01:56 by lisannehouk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	lenght_of_num(long num_to_check)
{
	int	lenght;

	lenght = 0;
	if (num_to_check < 0)
	{
		num_to_check = num_to_check * -1;
		lenght++;
	}
	if (num_to_check == 0)
		lenght++;
	while (num_to_check > 0)
	{
		num_to_check = num_to_check / 10;
		lenght++;
	}
	return (lenght);
}

static void	convert_num(long num_to_convert, int length, char *num_str)
{
	if (num_to_convert < 0)
	{
		num_str[0] = '-';
		num_to_convert = num_to_convert * -1;
	}
	while (num_to_convert > 0)
	{
		num_str[length] = num_to_convert % 10 + 48;
		num_to_convert = num_to_convert / 10;
		length--;
	}
}

char	*ft_itoa(int n)
{
	char	*num_str;
	long	num_to_convert;
	int		length_of_num;

	num_to_convert = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	length_of_num = lenght_of_num(num_to_convert);
	num_str = (char *)malloc(sizeof(char) * (length_of_num + 1));
	if (num_str == NULL)
		return (NULL);
	num_str[length_of_num] = '\0';
	length_of_num--;
	if (num_to_convert == 0)
		num_str[0] = '0';
	convert_num(num_to_convert, length_of_num, num_str);
	return (num_str);
}
