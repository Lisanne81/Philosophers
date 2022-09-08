/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/21 13:00:55 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/05/19 14:15:10 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*paste_str;
	size_t	index;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	paste_str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) \
			+ ft_strlen(s2) + 1));
	if (!paste_str)
		return (NULL);
	index = 0;
	while (*s1)
	{
		paste_str[index] = *s1;
		index++;
		s1++;
	}
	while (*s2)
	{
		paste_str[index] = *s2;
		index++;
		s2++;
	}
	paste_str[index] = '\0';
	return (paste_str);
}
