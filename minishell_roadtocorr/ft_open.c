/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/29 09:01:48 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_open_splr(int *in, int (*fd)[2], char *file)
{
	if (*in)
		close((*fd)[0]);
	(*fd)[0] = open(file, O_RDONLY);
	if ((*fd)[0] == -1)
	{
		g_exit_status = 1;
		perror(file);
		return (1);
	}
	*in = 1;
	return (0);
}

int	ft_open_dblr(int *in, int (*fd)[2], char *file, t_heredoc *heredoc)
{
	if (*in)
		close((*fd)[0]);
	(*fd)[0] = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if ((*fd)[0] == -1)
	{
		g_exit_status = 1;
		perror(file);
		return (1);
	}
	ft_print_list_heredoc(heredoc, (*fd)[0]);
	*in = 1;
	return (0);
}

int	ft_open_splw(int *out, int (*fd)[2], char *file)
{
	if (*out)
		close((*fd)[1]);
	(*fd)[1] = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if ((*fd)[1] == -1)
	{
		g_exit_status = 1;
		perror(file);
		return (1);
	}
	*out = 1;
	return (0);
}

int	ft_open_dblw(int *out, int (*fd)[2], char *file)
{
	if (*out)
		close((*fd)[1]);
	(*fd)[1] = open(file, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
	if ((*fd)[1] == -1)
	{
		g_exit_status = 1;
		perror(file);
		return (1);
	}
	*out = 1;
	return (0);
}
