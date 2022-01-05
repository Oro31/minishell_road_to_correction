/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/30 13:34:18 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_init_get_fd(int (*fd)[2], int *i, int *in, int *out)
{
	(*fd)[0] = 0;
	(*fd)[1] = 1;
	*i = -1;
	*in = 0;
	*out = 0;
}

void	ft_close_fd(int fd[2])
{
	if (fd[0])
		close(fd[0]);
	if (fd[1] > 1)
		close(fd[1]);
}

void	ft_dup2_fd(int fd[2])
{
	if (fd[0])
		dup2(fd[0], STDIN_FILENO);
	if (fd[1] > 1)
		dup2(fd[1], STDOUT_FILENO);
}

static int	ft_redir_in(int (*fd)[2], t_cmd **cmd, int i, int *in)
{
	if ((*cmd)->redir[i] == 1)
	{
		if (ft_open_splr(in, fd, (*cmd)->argv[i + 1]))
			return (1);
	}
	else if ((*cmd)->redir[i] == 2)
	{
		if (ft_open_dblr(in, fd, ".heredoc_tmp", (*cmd)->heredoc))
			return (1);
		if (ft_open_splr(in, fd, ".heredoc_tmp"))
			return (1);
	}
	return (0);
}

int	ft_get_fd(int (*fd)[2], t_cmd **cmd)
{
	int	i;
	int	in;
	int	out;

	ft_init_get_fd(fd, &i, &in, &out);
	while ((*cmd)->argv[++i])
	{
		if ((*cmd)->redir[i] == 1 || (*cmd)->redir[i] == 2)
		{
			if (ft_redir_in(fd, cmd, i, &in))
				return (1);
		}
		else if ((*cmd)->redir[i] == 3)
		{
			if (ft_open_splw(&out, fd, (*cmd)->argv[i + 1]))
				return (1);
		}
		else if ((*cmd)->redir[i] == 4)
		{
			if (ft_open_dblw(&out, fd, (*cmd)->argv[i + 1]))
				return (1);
		}
	}
	return (0);
}
