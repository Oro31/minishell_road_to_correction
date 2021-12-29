/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:10:26 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/22 01:46:41 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*some functions to manipulate strings*/

void	ft_print_str(char *str)
{
	int		i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*thise function is very usefull in ft_double_realloc*/

char	*ft_str_copy(char **str)
{
	char	*tmp;
	int		i;

	if (!*str)
		return (NULL);
	if (!ft_malloc_splchar(&tmp, ft_strlen(*str) + 1))
		return (NULL);
	i = -1;
	while ((*str)[++i])
		tmp[i] = (*str)[i];
	tmp[i] = '\0';
	free(*str);
	*str = NULL;
	return (tmp);
}

char	*ft_str_copy_nofree(char *str)
{
	char	*tmp;
	int		i;

	if (!str)
		return (NULL);
	if (!ft_malloc_splchar(&tmp, ft_strlen(str) + 1))
		return (NULL);
	i = -1;
	while (str[++i])
		tmp[i] = str[i];
	tmp[i] = '\0';
	return (tmp);
}

int	ft_strncomp(char *str, char *comp, int n)
{
	int	i;

	i = 0;
	if (!str)
	{
		if (!comp)
			return (0);
		else
			return ('\0' - comp[0]);
	}
	else if (!comp)
		return (str[0]);
	if (ft_strlen(str) < n)
		return (-999);
	while (str[i] && comp[i] && str[i] == comp[i] && i < n)
		i++;
	return (str[i] - comp[i]);
}
