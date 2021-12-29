/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/25 22:57:02 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**ft_split(char **path, char c)
{
	char	**ret;
	char	*str;
	int		i;

	if (!*path)
		return (NULL);
	ret = NULL;
	str = NULL;
	i = -1;
	while ((*path)[++i])
	{
		if ((*path)[i] == c)
			ret = ft_double_realloc(&str, &ret);
		else
			str = ft_realloc(&str, (*path)[i]);
	}
	ret = ft_double_realloc(&str, &ret);
	free(*path);
	*path = NULL;
	return (ret);
}

char	**ft_get_execve_argv(char **argv)
{
	char	**ret;
	int		i;

	ret = NULL;
	i = 0;
	while (argv[i])
		i++;
	if (!ft_malloc_dblchar(&ret, i))
		return (NULL);
	while (--i > 0)
	{
		printf("%d\n", i);
		ret[i - 1] = ft_str_copy_nofree(argv[i]);
	}
	return (ret);
}

void	ft_free_ctab(char ***ctab)
{
	int	i;

	i = -1;
	while ((*ctab)[++i])
	{
		free((*ctab)[i]);
		(*ctab)[i] = NULL;
	}
	free(*ctab);
	*ctab = NULL;
}
