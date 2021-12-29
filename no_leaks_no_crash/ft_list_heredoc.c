/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:05:31 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/29 09:00:58 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_heredoc	*ft_eadd_tolist_heredoc(t_heredoc *list, char *line)
{
	t_heredoc	*newelem;
	t_heredoc	*tmp;

	newelem = malloc(sizeof(t_heredoc));
	if (!newelem)
	{
		perror("malloc failed\n");
		return (NULL);
	}
	newelem->line = line;
	newelem->nxt = NULL;
	if (list == NULL)
		return (newelem);
	else
	{
		tmp = list;
		while (tmp->nxt != NULL)
			tmp = tmp->nxt;
		tmp->nxt = newelem;
		return (list);
	}
}

void	ft_free_list_heredoc(t_heredoc **list)
{
	t_heredoc	*tmp;

	tmp = NULL;
	if (list)
	{
		if (*list)
		{
			while (*list)
			{
				tmp = (*list)->nxt;
				free((*list)->line);
				(*list)->line = NULL;
				free(*list);
				*list = NULL;
				*list = tmp;
			}
		}
	}
}

void	ft_print_list_heredoc(t_heredoc *list, int fd)
{
	t_heredoc	*tmp;

	if (list != NULL)
	{
		tmp = list;
		while (tmp)
		{
			write(fd, tmp->line, ft_strlen(tmp->line));
			write(fd, "\n", 1);
			tmp = tmp->nxt;
		}
	}
}
