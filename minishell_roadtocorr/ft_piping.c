/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/28 11:23:35 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_dup2_close_fd(t_pipe *piping)
{
	if (piping->i != 0)
		dup2(piping->oldfd, STDIN_FILENO);
	if (piping->tmp->nxt)
		dup2(piping->fd[1], STDOUT_FILENO);
	close(piping->fd[0]);
	close(piping->fd[1]);
	close(piping->oldfd);
}

static t_cmd	*ft_nxt_pipe(t_pipe *piping)
{
	dup2(piping->fd[0], piping->oldfd);
	close(piping->fd[0]);
	close(piping->fd[1]);
	piping->i++;
	return (piping->tmp->nxt);
}

static int	ft_execve_in_pipe(t_env **env, t_cmd **cmd, char *path)
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
			perror((*cmd)->argv[0]);
			return (1);
		}
	}
	return (0);
}

static int	ft_exec_pipe(t_env **env, t_cmd **cmd)
{
	char	**path_split;	
	char	*path;
	int		fd[2];

	if (ft_is_builtin((*cmd)->argv[0]))
	{
		ft_exec_builtin(env, cmd);
		return (0);
	}
	if (ft_get_fd(&fd, cmd))
		return (1);
	ft_dup2_fd(fd);
	path = ft_get_env(*env, "PATH");
	if (!path)
		return (ft_print_ex_error("No such file or directory",
				(*cmd)->argv[0]));
	path_split = ft_split(&path, ':');
	path = ft_find_valid_path(&path_split, (*cmd)->argv[0]);
	ft_execve_in_pipe(env, cmd, path);
	free(path);
	ft_free_ctab(&path_split);
	return (ft_print_ex_error("command not found", (*cmd)->argv[0]));
}

void	ft_piping(t_env **env, t_cmd **cmd)
{
	t_pipe				piping;

	ft_set_sigaction(&piping.action, 'p');
	piping.i = 0;
	piping.tmp = *cmd;
	piping.oldfd = dup(STDIN_FILENO);
	while (piping.tmp)
	{
		pipe(piping.fd);
		piping.pid = fork();
		if (!piping.pid)
		{
			ft_dup2_close_fd(&piping);
			g_exit_status = ft_exec_pipe(env, &piping.tmp);
			exit(g_exit_status);
		}
		else if (piping.pid < 0)
			write(2, "error pid\n", 10);
		piping.tmp = ft_nxt_pipe(&piping);
	}
	close(piping.oldfd);
	piping.i = -1;
	while (++piping.i < ft_size_list_cmd(*cmd))
		wait(&piping.status);
	g_exit_status = ft_get_exit_status(piping.status);
}
