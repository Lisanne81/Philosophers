/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 08:31:21 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/01/21 17:43:22 by lisannehouk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	size_t	strlength;

	strlength = 0;
	while (str[strlength] != '\0')
	{
		strlength++;
	}
	return (strlength);
}
