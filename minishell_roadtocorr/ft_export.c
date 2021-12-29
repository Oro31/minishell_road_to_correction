/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/28 10:40:30 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_export_already_exist(t_env **tmp, char **name, char *value)
{
	free(*name);
	free((*tmp)->value);
	(*tmp)->value = value;
}

static void	ft_init_export(t_env **tmp, char **name, char **value, int *i)
{
	*tmp = NULL;
	*name = NULL;
	*value = NULL;
	*i = -1;
}

int	ft_is_arg_export_valid(char *arg)
{
	int	i;

	i = 0;
	if (!ft_is_alpha(arg[i]) && arg[i] != '_')
		return (0);
	while (arg[++i] && arg[i] != '=')
		if (!ft_is_alpha(arg[i]) && !ft_is_digit(arg[i]) && arg[i] != '_')
			return (0);
	return (1);
}

int	ft_hdl_arg_export(t_env **env, char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (ft_is_arg_export_valid(argv[i]))
			ft_export(env, argv[i]);
		else
		{
			g_exit_status = 1;
			write(2, "export: '", 9);
			write(2, argv[i], ft_strlen(argv[i]));
			write(2, "': not a valid identifier\n", 26);
		}
	}
	return (0);
}

int	ft_export(t_env **env, char *arg)
{
	t_env	*tmp;
	char	*name;
	char	*value;
	int		i;

	ft_init_export(&tmp, &name, &value, &i);
	if (!arg)
		return (0);
	while (arg[++i] && arg[i] != '=')
		name = ft_realloc(&name, arg[i]);
	if (!arg[i])
	{
		free(name);
		return (0);
	}
	while (arg[++i])
		value = ft_realloc(&value, arg[i]);
	tmp = *env;
	while (tmp && ft_strcomp(name, tmp->name) != 0)
		tmp = tmp->nxt;
	if (!tmp)
		*env = ft_eadd_tolist_env(*env, name, value);
	else
		ft_export_already_exist(&tmp, &name, value);
	return (0);
}
