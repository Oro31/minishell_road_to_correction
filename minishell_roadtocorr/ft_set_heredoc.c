/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/29 09:00:09 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_is_eof_quoted(char *eof)
{
	int	i;

	i = -1;
	while (eof[++i])
	{
		if (ft_is_char_quoted(eof, i, 0, eof[i]))
			return (1);
	}
	return (0);
}

t_heredoc	*ft_set_heredoc(t_env *env, char **cmd_char, int *red_tab)
{
	t_heredoc	*heredoc;
	char		*eof;
	int			ret;
	int			quoted;
	int			i;

	eof = NULL;
	heredoc = NULL;
	quoted = 0;
	ret = 0;
	i = -1;
	while (cmd_char[++i])
	{
		if (red_tab[i] == 2)
		{
			ft_free_list_heredoc(&heredoc);
			quoted = ft_is_eof_quoted(cmd_char[i + 1]);
			eof = ft_clean_str(cmd_char[i + 1]);
			while (!ret)
				ret = ft_heredoc(env, &heredoc, eof, quoted);
			free(eof);
			eof = NULL;
		}
	}
	return (heredoc);
}
