/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 12:33:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/29 08:24:49 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_exec_line(t_env **env, t_cmd **cmd, char *line)
{
	if ((*cmd)->nxt)
		ft_piping(env, cmd);
	else if (ft_strcomp("exit", (*cmd)->argv[0]) == 0)
		ft_exit(env, cmd, line, (*cmd)->argv);
	else if (ft_is_builtin((*cmd)->argv[0]))
		ft_exec_builtin(env, cmd);
	else
		ft_hdl_arg_execve(env, cmd);
}

static int	ft_is_eof(t_env **env, t_cmd **cmd, char **line)
{
	if (!*line)
	{
		free(*line);
		ft_free_list_cmd(cmd);
		ft_free_list_env(env);
		return (1);
	}
	return (0);
}

static int	ft_syntax_error(char **line)
{
	free(*line);
	*line = NULL;
	g_exit_status = 2;
	write(2, "syntax error\n", 13);
	return (0);
}

static void	ft_parse_readline(t_env *env, t_cmd **cmd, char **line)
{
	t_heredoc	*heredoc;
	char		**cmd_char;
	char		**pipe_char;
	int			*red_tab;
	int			i;

	heredoc = NULL;
	pipe_char = NULL;
	pipe_char = ft_pipe_split(line);
	pipe_char = ft_set_redir(pipe_char);
	i = -1;
	while (pipe_char[++i])
	{
		cmd_char = NULL;
		red_tab = NULL;
		cmd_char = ft_cmdline_split(&pipe_char[i]);
		red_tab = ft_set_redir_tab(cmd_char);
		heredoc = ft_set_heredoc(env, cmd_char, red_tab);
		cmd_char = ft_dollar_parse(env, cmd_char);
		cmd_char = ft_clean_cmdchar(cmd_char);
		*cmd = ft_eadd_tolist_cmd(*cmd, cmd_char, red_tab, heredoc);
	}
	free(pipe_char);
}

int	ft_prompt(t_env **env)
{
	t_cmd				*cmd;
	struct sigaction	action;
	char				*line;

	cmd = NULL;
	line = NULL;
	ft_set_sigaction(&action, 'm');
	action.sa_handler = ft_main_handler;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &action, NULL);
	line = readline("$>");
	if (ft_is_eof(env, &cmd, &line))
		return (1);
	if (ft_strlen(line) > 0)
	{
		add_history(line);
		if (!ft_parse_error(line))
			return (ft_syntax_error(&line));
		ft_parse_readline(*env, &cmd, &line);
		ft_exec_line(env, &cmd, line);
	}
	free(line);
	ft_free_list_cmd(&cmd);
	return (0);
}
