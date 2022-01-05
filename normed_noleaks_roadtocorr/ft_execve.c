/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2022/01/05 17:33:23 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_init_exec(t_exec *exec)
{
	exec->fd[0] = 0;
	exec->fd[1] = 1;
	exec->status = 0;
}

int	ft_execve(char **argv, t_env **env)
{
	char	**path_split;
	char	**env_p;
	char	*path;
	int		env_path;

	path_split = NULL;
	path = ft_get_env(*env, "PATH", &env_path);
	path_split = ft_split(&path, ':');
	path = ft_find_valid_path(&path_split, argv[0]);
	if (!env_path && access(path, X_OK))
		return (ft_print_ex_error("No such file or directory", argv[0],
				&path_split, path));
	env_p = ft_tenv_to_envp(*env);
	if (execve(path, argv, env_p) < 0)
	{
		ft_free_ctab(&env_p);
		g_exit_status = errno;
	}
	return (ft_print_ex_error("command not found", argv[0], &path_split, path));
}

void	ft_hdl_arg_execve(t_env **env, t_cmd **cmd)
{
	t_exec	exec;
	char	**argv;

	ft_init_exec(&exec);
	exec.pid = fork();
	signal(SIGQUIT, ft_fork_handler);
	signal(SIGINT, ft_fork_handler);
	if (!exec.pid)
	{
		if (ft_get_fd(&exec.fd, cmd))
		{
			ft_free_execve(env, cmd, NULL);
			exit(g_exit_status);
		}
		ft_dup2_fd(exec.fd);
		argv = ft_clean_redir(cmd);
		g_exit_status = ft_execve(argv, env);
		ft_free_execve(env, cmd, &argv);
		exit(g_exit_status);
	}
	else if (exec.pid < 0)
		write(2, "error pid\n", 10);
	ft_close_fd(exec.fd);
	wait(&exec.status);
	g_exit_status = ft_get_exit_status(exec.status);
}
