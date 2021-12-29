/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/28 11:14:06 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_set_path(char *path, char *value)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = -1;
	while (path[++i])
		ret = ft_realloc(&ret, path[i]);
	ret = ft_realloc(&ret, '/');
	i = -1;
	while (value[++i])
		ret = ft_realloc(&ret, value[i]);
	return (ret);
}

int	ft_print_ex_error(char *error, char *cmd)
{
	g_exit_status = 127;
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (127);
}

char	*ft_find_valid_path(char ***path_split, char *cmd)
{
	char	*path;
	int		i;

	path = NULL;
	i = -1;
	while ((*path_split)[++i])
	{
		path = ft_set_path((*path_split)[i], cmd);
		if (!access(path, X_OK))
		{
			i = -1;
			while ((*path_split)[++i])
			{
				free((*path_split)[i]);
				(*path_split)[i] = NULL;
			}
			free(*path_split);
			*path_split = NULL;
			return (path);
		}
		free(path);
		path = NULL;
	}
	return (NULL);
}

int	ft_execve(char **argv, t_env **env)
{
	char	**path_split;
	char	**env_p;
	char	*path;

	path = ft_get_env(*env, "PATH");
	if (!path)
		return (ft_print_ex_error("No such file or directory", argv[0]));
	path_split = ft_split(&path, ':');
	path = ft_find_valid_path(&path_split, argv[0]);
	if (path)
	{
		env_p = ft_tenv_to_envp(*env);
		if (execve(path, argv, env_p) < 0)
		{
			free(path);
			ft_free_ctab(&path_split);
			ft_free_ctab(&env_p);
			g_exit_status = errno;
			perror(argv[0]);
			return (g_exit_status);
		}
	}
	free(path);
	ft_free_ctab(&path_split);
	return (ft_print_ex_error("command not found", argv[0]));
}

void	ft_hdl_arg_execve(t_env **env, t_cmd **cmd)
{
	pid_t				pid;
	struct sigaction	action;
	char				**argv;
	int					fd[2];
	int					status;

	ft_set_sigaction(&action, 'f');
	fd[0] = 0;
	fd[1] = 1;
	pid = fork();
	if (!pid)
	{
		if (ft_get_fd(&fd, cmd))
			return ;
		ft_dup2_fd(fd);
		argv = ft_clean_redir(cmd);
		g_exit_status = ft_execve(argv, env);
		ft_free_ctab(&argv);
		exit(g_exit_status);
	}
	else if (pid < 0)
		write(2, "error pid\n", 10);
	ft_close_fd(fd);
	wait(&status);
	g_exit_status = ft_get_exit_status(status);
}
