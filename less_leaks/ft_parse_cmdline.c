/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmdline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/23 00:29:26 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*the function ft_cmdline_split is used to create a table of strings
from a simple string, the separateur used is space,
the separateur will be valid if it's not between quotes
the simple string is freed at the end of the function
the function return a table of strings
that you will have to free before the end of your program*/

static int	ft_init_cmdline_split(char ***ret, char **str, int *i, int *j)
{
	*ret = NULL;
	*str = NULL;
	*i = -1;
	*j = 0;
	return (1);
}

static int	ft_realloc_previous_str(char **str, char ***ret, int i)
{
	if (*str)
		*ret = ft_double_realloc(str, ret);
	return (i);
}

char	**ft_cmdline_split(char **line)
{
	char	**ret;
	char	*str;
	int		i;
	int		j;

	if (!ft_init_cmdline_split(&ret, &str, &i, &j))
		return (NULL);
	while ((*line)[++i])
	{
		if ((*line)[i] == ' ')
		{
			if (!ft_is_char_quoted(*line, i, j, (*line)[i]) && i > 0)
				i = ft_realloc_previous_str(&str, &ret, i);
			else
				str = ft_realloc(&str, (*line)[i]);
		}
		else
			str = ft_realloc(&str, (*line)[i]);
	}
	free(*line);
	*line = NULL;
	return (ft_double_realloc(&str, &ret));
}
