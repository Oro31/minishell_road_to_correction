/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2022/01/05 15:51:26 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_set_path(char *path, char *value)
{
	char	*ret;
	int		i;

	if (!path)
		return (NULL);
	ret = NULL;
	i = -1;
	while (path[++i])
		ret = ft_realloc(&ret, path[i]);
	ret = ft_realloc(&ret, '/');
	i = -1;
	while (value[++i])
		ret = ft_realloc(&ret, value[i]);
	return (ret);
}

int	ft_print_ex_error(char *error, char *cmd, char ***path_split, char *path)
{
	g_exit_status = 127;
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	free(path);
	ft_free_ctab(path_split);
	return (127);
}

char	*ft_find_valid_path(char ***path_split, char *cmd)
{
	char	*path;
	int		i;

	if (!*path_split)
		return (ft_str_copy_nofree(cmd));
	i = -1;
	while ((*path_split)[++i])
	{
		path = ft_set_path((*path_split)[i], cmd);
		if (!access(path, X_OK))
		{
			i = -1;
			while ((*path_split)[++i])
			{
				free((*path_split)[i]);
				(*path_split)[i] = NULL;
			}
			free(*path_split);
			*path_split = NULL;
			return (path);
		}
		free(path);
		path = NULL;
	}
	return (ft_str_copy_nofree(cmd));
}
