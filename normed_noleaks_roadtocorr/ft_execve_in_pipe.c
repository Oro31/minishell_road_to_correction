/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_in_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2022/01/05 16:55:40 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_execve_in_pipe(t_env **env, t_cmd **cmd, char *path)
{
	char	**argv;
	char	**env_p;

	env_p = NULL;
	argv = NULL;
	if (path)
	{
		argv = ft_clean_redir(cmd);
		env_p = ft_tenv_to_envp(*env);
		if (execve(path, argv, env_p) < 0)
		{
			ft_free_ctab(&argv);
			ft_free_ctab(&env_p);
			return (1);
		}
	}
	return (0);
}
