/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_realloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:04:56 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/21 20:36:35 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*these function add string to a table of string
everything that is not returned is freed*/

char	**ft_double_realloc(char **str, char ***split)
{
	char	**tmp;
	int		i;

	tmp = NULL;
	if (!*split)
	{
		if (!*str)
			return (NULL);
		if (!ft_malloc_dblchar(&tmp, 2))
			return (NULL);
		tmp[0] = ft_str_copy(str);
		return (tmp);
	}
	i = 0;
	while ((*split)[i])
		i++;
	if (!ft_malloc_dblchar(&tmp, i + 2))
		return (NULL);
	tmp[i] = ft_str_copy(str);
	while (--i >= 0)
		tmp[i] = ft_str_copy(&(*split)[i]);
	free(*split);
	*split = NULL;
	return (tmp);
}

/*these function add char to a string
everything that is not returned is freed*/

char	*ft_realloc(char **str, char c)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	if (!*str)
	{
		if (!ft_malloc_splchar(&tmp, 2))
			return (NULL);
		tmp[0] = c;
		return (tmp);
	}
	i = ft_strlen(*str);
	if (!ft_malloc_splchar(&tmp, i + 2))
		return (NULL);
	tmp[i] = c;
	while (--i >= 0)
		tmp[i] = (*str)[i];
	free(*str);
	*str = NULL;
	return (tmp);
}
