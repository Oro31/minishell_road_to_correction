/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_cmdchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 12:33:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/29 07:07:18 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*this set of function clean quotes from a table of string
it only clean real quotes, not quotes that are consider as char
the function ft_clean_cmdchar allocate memory with malloc
you need to free it before exiting your program*/

static void	ft_fill_clean_str(char **tmp, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] == ' ')
		i++;
	j = 0;
	while (str[i])
	{
		if (str[i] != S_QUOTE && str[i] != D_QUOTE)
		{
			(*tmp)[j] = str[i];
			j++;
		}
		else if (ft_is_quote_needed(str, i))
		{
			(*tmp)[j] = str[i];
			j++;
		}
		i++;
	}
}

char	*ft_clean_str(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] == ' ')
		i++;
	j = 0;
	while (str[i])
	{
		if (str[i] != S_QUOTE && str[i] != D_QUOTE)
			j++;
		else if (ft_is_quote_needed(str, i))
			j++;
		i++;
	}
	if (!ft_malloc_splchar(&tmp, j + 1))
		return (NULL);
	ft_fill_clean_str(&tmp, str);
	return (tmp);
}

char	**ft_clean_cmdchar(char **cmd_char)
{
	char	**tmp;
	int		i;

	i = 0;
	while (cmd_char[i])
		i++;
	if (!ft_malloc_dblchar(&tmp, i + 1))
		return (NULL);
	i = -1;
	while (cmd_char[++i])
	{
		tmp[i] = ft_clean_str(cmd_char[i]);
		free(cmd_char[i]);
	}
	free(cmd_char);
	return (tmp);
}
