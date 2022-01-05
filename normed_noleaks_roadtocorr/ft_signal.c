/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 12:33:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/30 15:01:01 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_main_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	ft_fork_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_exit_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		g_exit_status = 131;
	}	
}

void	ft_pipe_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_exit_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		g_exit_status = 131;
	}	
}

void	ft_set_sigaction(struct sigaction *action, char which)
{
	if (which == 'p')
		(*action).sa_handler = ft_pipe_handler;
	else if (which == 'f')
		(*action).sa_handler = ft_fork_handler;
	(*action).sa_flags = 0;
	ft_memset((void *)&(*action).sa_mask, '\0', sizeof(sigset_t));
	if (which != 'm')
	{
		sigaction(SIGINT, action, NULL);
		sigaction(SIGQUIT, action, NULL);
	}
}
