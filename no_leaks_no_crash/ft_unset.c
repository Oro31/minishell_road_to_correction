/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/28 10:43:41 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_hdl_arg_unset(t_env **env, char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (ft_is_arg_export_valid(argv[i]))
			ft_unset(env, argv[i]);
		else
		{
			g_exit_status = 1;
			write(2, "env: '", 6);
			write(2, argv[i], ft_strlen(argv[i]));
			write(2, "': not a valid identifier\n", 26);
		}
	}
	return (0);
}

int	ft_unset(t_env **env, char *name)
{
	t_env	*tmp;
	int		i;

	if (!*env)
		return (0);
	i = 1;
	tmp = *env;
	while (tmp && ft_strcomp(name, tmp->name) != 0)
	{
		tmp = tmp->nxt;
		i++;
	}
	if (i == 1)
	{
		*env = (*env)->nxt;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		return (0);
	}
	*env = ft_ndelete_env(*env, i);
	g_exit_status = 0;
	return (0);
}
