/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/28 10:37:20 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_error_msg(char *msg)
{
	g_exit_status = 1;
	write(2, "cd: ", 4);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

static char	*ft_set_arg(char *name, char *value)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = -1;
	while (name[++i])
		ret = ft_realloc(&ret, name[i]);
	ret = ft_realloc(&ret, '=');
	i = -1;
	while (value[++i])
		ret = ft_realloc(&ret, value[i]);
	free(value);
	return (ret);
}

int	ft_hdl_arg_cd(t_env **env, char **argv)
{
	t_env	*tmp;

	if (!argv[1])
	{
		tmp = *env;
		while (tmp && ft_strcomp("HOME", tmp->name) != 0)
			tmp = tmp->nxt;
		if (!tmp)
			return (ft_error_msg("HOME not set"));
		else
			return (ft_cd(env, tmp->value));
	}
	else if (!argv[2])
		return (ft_cd(env, argv[1]));
	else
		return (ft_error_msg("too many arguments"));
}

int	ft_cd(t_env **env, char *dir)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = NULL;
	old_pwd = ft_get_env(*env, "PWD");
	if (dir && chdir(dir))
	{
		free(old_pwd);
		g_exit_status = 1;
		write(2, "cd: ", 4);
		write(2, dir, ft_strlen(dir));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	pwd = ft_set_arg("PWD", getcwd(NULL, 0));
	if (old_pwd)
		old_pwd = ft_set_arg("OLDPWD", old_pwd);
	ft_export(env, old_pwd);
	ft_export(env, pwd);
	free(old_pwd);
	free(pwd);
	g_exit_status = 0;
	return (0);
}
