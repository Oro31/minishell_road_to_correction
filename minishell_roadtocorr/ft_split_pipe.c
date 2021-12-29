/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/23 00:32:11 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*the function ft_pipe_split is used to create a table of strings
from the line extracted with readline, the separateur used is | 
the separateur will be valid if it's not between quotes
the line is freed at the end of the function
the function return a table of strings
that you will have to free before the end of your program*/

static int	ft_init_pipe_split(char ***ret, char **str, int *i, int *j)
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
		(*ret) = ft_double_realloc(str, ret);
	return (i);
}

static int	ft_is_space_needed(char *rdline, int i)
{
	if (rdline[i] != ' ')
		return (1);
	if (ft_is_char_quoted(rdline, i, 0, rdline[i]))
		return (1);
	else if (i == 0)
		return (0);
	else if (rdline[i - 1] == ' ' || rdline[i - 1] == '|')
		return (0);
	else if (rdline[i + 1] == '\0' || rdline[i + 1] == '|'
		|| rdline[i + 1] == ' ')
		return (0);
	else
		return (1);
}

char	**ft_pipe_split(char **rdline)
{
	char	**ret;
	char	*str;
	int		i;
	int		j;

	if (!ft_init_pipe_split(&ret, &str, &i, &j))
		return (NULL);
	while ((*rdline)[++i])
	{
		if ((*rdline)[i] == '|')
		{
			if (!ft_is_char_quoted(*rdline, i, j, (*rdline)[i]))
				j = ft_realloc_previous_str(&str, &ret, i);
			else
				str = ft_realloc(&str, (*rdline)[i]);
		}
		else if ((*rdline)[i] != ' ' || ft_is_space_needed(*rdline, i))
			str = ft_realloc(&str, (*rdline)[i]);
	}
	free(*rdline);
	*rdline = NULL;
	return (ft_double_realloc(&str, &ret));
}
