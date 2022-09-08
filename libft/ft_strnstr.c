/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 20:15:20 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/08/17 17:49:59 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	j;

	if (!needle[0])
		return ((char *)haystack);
	index = 0;
	while (haystack[index] && index < len)
	{
		j = 0;
		while (haystack[index + j] && needle[j] && \
		index + j < len && \
					haystack[index + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)(haystack + index));
		index++;
	}
	return (0);
}
