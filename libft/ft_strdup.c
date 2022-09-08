/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/01 08:08:00 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/05/19 14:16:08 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*str_1;
	size_t	size;

	size = ft_strlen(s) + 1;
	str_1 = (char *)malloc(sizeof(char) * size);
	if (str_1 == NULL)
		return (NULL);
	return (ft_memcpy(str_1, s, size));
}
