/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 12:02:32 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/05/19 14:19:03 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	index;

	index = 0;
	if (n == 0 || dst == src)
		return (dst);
	while (index < n)
	{
		((char *)dst)[index] = ((char *)src)[index];
		index++;
	}
	return (dst);
}
