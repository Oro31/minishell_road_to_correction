/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 12:33:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/28 08:37:07 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_is_builtin(char *exe)
{
	if (ft_strcomp("env", exe) == 0)
		return (1);
	else if (ft_strcomp("cd", exe) == 0)
		return (1);
	else if (ft_strcomp("unset", exe) == 0)
		return (1);
	else if (ft_strcomp("export", exe) == 0)
		return (1);
	else if (ft_strcomp("pwd", exe) == 0)
		return (1);
	else if (ft_strcomp("echo", exe) == 0)
		return (1);
	else if (ft_strcomp("exit", exe) == 0)
		return (1);
	return (0);
}

static void	ft_which_builtin(t_env **env, char **argv)
{
	if (ft_strcomp("env", argv[0]) == 0)
		ft_env(*env, argv);
	else if (ft_strcomp("cd", argv[0]) == 0)
		ft_hdl_arg_cd(env, argv);
	else if (ft_strcomp("unset", argv[0]) == 0)
		ft_hdl_arg_unset(env, argv);
	else if (ft_strcomp("export", argv[0]) == 0)
		ft_hdl_arg_export(env, argv);
	else if (ft_strcomp("pwd", argv[0]) == 0)
		ft_pwd();
	else if (ft_strcomp("echo", argv[0]) == 0)
		ft_echo(argv);
	else if (ft_strcomp("exit", argv[0]) == 0)
		ft_exit(NULL, NULL, NULL, argv);
}

void	ft_exec_builtin(t_env **env, t_cmd **cmd)
{
	char	**argv;
	int		oldfd;
	int		fd[2];

	oldfd = dup(STDOUT_FILENO);
	if (ft_get_fd(&fd, cmd))
		return ;
	argv = ft_clean_redir(cmd);
	if (fd[1] > 1)
		dup2(fd[1], STDOUT_FILENO);
	ft_which_builtin(env, argv);
	ft_free_ctab(&argv);
	dup2(oldfd, STDOUT_FILENO);
	if (fd[1] != 1)
		close(fd[1]);
	close(oldfd);
}
