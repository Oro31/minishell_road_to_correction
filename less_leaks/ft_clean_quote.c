/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 08:36:54 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/21 13:40:58 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*these set of functions is used to know if a quote
is a quote or a simple char,
the function ft_is_quote_needed return 1 if the quote
need to be considered as a simple char*/

int	ft_is_quote(char c)
{
	return (c == S_QUOTE || c == D_QUOTE);
}

static int	ft_is_open_q_close(char *arg, int i, char open_q)
{
	int	j;

	j = i + 1;
	while (arg[j] && (arg[j] != open_q))
		j++;
	if (open_q)
		if (arg[j] == open_q)
			return (1);
	return (0);
}

static char	ft_new_open_q(char *arg, char open_q, int k)
{
	int	i;

	i = 0;
	if (!open_q)
		return (arg[k]);
	else if (open_q == arg[k])
		return (0);
	else
	{
		if (!ft_is_open_q_close(arg, k, open_q))
			return (arg[k]);
		return (open_q);
	}
}

int	ft_is_quote_needed(char *arg, int i)
{
	int		k;
	char	open_q;

	open_q = 0;
	k = -1;
	while (++k < i)
	{
		if (ft_is_quote(arg[k]))
			open_q = ft_new_open_q(arg, open_q, k);
	}
	if (arg[i] == open_q)
		return (0);
	else if (!open_q && ft_is_open_q_close(arg, i, arg[i]))
		return (0);
	else if (ft_is_open_q_close(arg, i, open_q))
		return (1);
	else
		return (1);
}
