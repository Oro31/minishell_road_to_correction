/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2022/01/05 17:45:44 by rvalton          ###   ########.fr       */
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
	if (!piping->tmp->nxt)
		piping->i = -1;
	piping->i++;
	return (piping->tmp->nxt);
}

static void	ft_init_piping(t_pipe *piping, t_cmd *cmd)
{
	piping->i = 0;
	piping->tmp = cmd;
	piping->oldfd = dup(STDIN_FILENO);
}

static int	ft_exec_pipe(t_env **env, t_cmd **cmd)
{
	char	**path_split;	
	char	*path;
	int		env_path;
	int		fd[2];

	if (ft_get_fd(&fd, cmd))
		return (1);
	ft_dup2_fd(fd);
	if (ft_is_builtin((*cmd)->argv[0]))
	{
		ft_exec_builtinpipe(env, cmd);
		return (g_exit_status);
	}
	path = ft_get_env(*env, "PATH", &env_path);
	path_split = ft_split(&path, ':');
	path = ft_find_valid_path(&path_split, (*cmd)->argv[0]);
	if (!env_path && access(path, X_OK))
		return (ft_print_ex_error("No such file or directory",
				(*cmd)->argv[0], &path_split, path));
	ft_execve_in_pipe(env, cmd, path);
	return (ft_print_ex_error("command not found", (*cmd)->argv[0],
			&path_split, path));
}

void	ft_piping(t_env **env, t_cmd **cmd)
{
	t_pipe				piping;

	ft_init_piping(&piping, *cmd);
	while (piping.tmp)
	{
		pipe(piping.fd);
		piping.pid = fork();
		signal(SIGQUIT, ft_pipe_handler);
		signal(SIGINT, ft_pipe_handler);
		if (!piping.pid)
		{
			ft_dup2_close_fd(&piping);
			g_exit_status = ft_exec_pipe(env, &piping.tmp);
			ft_free_execve(env, cmd, NULL);
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
