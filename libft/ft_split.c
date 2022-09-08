/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 12:08:33 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/01/21 17:43:08 by lisannehouk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_word_counter(const char *str, char c)
{
	int	word_counter;
	int	index;

	if (!str)
		return (0);
	index = 0;
	word_counter = 0;
	while (str[index] != '\0')
	{
		if (str[index] != c && (str[index + 1] == c || str[index + 1] == '\0'))
			word_counter++;
		index++;
	}
	return (word_counter);
}

static int	ft_w_len(const char *str, char c, int tracker)
{
	int	word_length;

	word_length = 0;
	while (str[tracker] != c && str[tracker] != '\0')
	{
		word_length++;
		tracker++;
	}
	return (word_length);
}

static void	*ft_free_mem(char **strpt)
{
	int		index;

	index = 0;
	while (strpt[index])
	{
		free(strpt[index]);
		index++;
	}
	free(strpt[index]);
	free(strpt);
	return (NULL);
}

static char	**ft_str_chop(const char *str, char **loc, char c, int word)
{
	int	index;
	int	x;
	int	y;

	index = 0;
	x = 0;
	while (str[index] != '\0' && x < word)
	{
		y = 0;
		while (str[index] == c)
			index++;
		loc[x] = (char *)malloc(sizeof(char) * ft_w_len(str, c, index) + 1);
		if (loc[x] == NULL)
			return (ft_free_mem(loc));
		while (str[index] != '\0' && str[index] != c)
		{
			loc[x][y] = str[index];
			y++;
			index++;
		}
		loc[x][y] = '\0';
		x++;
	}
	loc[x] = 0;
	return (loc);
}

char	**ft_split(char const *str, char c)
{
	int			words;
	char		**strpt;

	if (str == NULL)
		return (NULL);
	words = ft_word_counter(str, c);
	strpt = (char **)malloc(sizeof(char *) * (words + 1));
	if (strpt == NULL)
		return (NULL);
	return (ft_str_chop(str, strpt, c, words));
}
