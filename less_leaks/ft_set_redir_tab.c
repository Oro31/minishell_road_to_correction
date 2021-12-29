/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_redir_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/28 04:28:18 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_is_arg_redir(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && ft_is_redir(arg[i]))
		i++;
	if (i > 0 && i < 3 && arg[i] == '\0')
		return (1);
	return (0);
}

static int	ft_which_redir(char *arg)
{
	if (arg[0] == '<' && arg[1] == '<')
		return (2);
	else if (arg[0] == '<')
		return (1);
	else if (arg[0] == '>' && arg[1] == '>')
		return (4);
	else
		return (3);
}

int	*ft_set_redir_tab(char **cmd_char)
{
	int	*ret;
	int	i;
	int	j;

	i = 0;
	while (cmd_char[i])
		i++;
	if (!ft_malloc_splint(&ret, i))
		return (0);
	j = -1;
	while (++j < i)
		ret[j] = 0;
	j = -1;
	while (cmd_char[++j])
	{
		if (ft_is_arg_redir(cmd_char[j]))
			ret[j] = ft_which_redir(cmd_char[j]);
	}
	return (ret);
}
