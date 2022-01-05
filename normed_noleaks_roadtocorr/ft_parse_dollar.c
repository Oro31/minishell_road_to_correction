/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 08:36:54 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/29 08:53:04 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*the function ft_dollar_parse is used to replace $abcd
by the value of the the environnement variable abcd
everything not returned is freed
the function return a table of strings
that you will have to free before the end of your program*/

static int	ft_moove_index(char *str, int i)
{
	int	j;

	j = i;
	if (str[i + 1] == '?')
		return (j + 2);
	while (ft_is_digit(str[++j]) || ft_is_alpha(str[j]) || str[j] == '_')
		;
	return (j);
}

static void	ft_init_fill(char **dol, int *i, int *j)
{
	*dol = NULL;
	*i = -1;
	*j = -1;
}

static void	ft_fill_dollar(t_env *env, char **tmp, char *str)
{
	char	*dol;
	int		i;
	int		j;
	int		k;

	ft_init_fill(&dol, &i, &j);
	while (str[++i])
	{
		if (ft_is_dollar(str, i))
		{
			dol = ft_get_dollar_value(env, str, i);
			k = -1;
			while (dol[++k])
				(*tmp)[++j] = dol[k];
			free(dol);
			i = ft_moove_index(str, i);
			if (str[i])
				i--;
		}
		else
			(*tmp)[++j] = str[i];
		if (!str[i])
			i--;
	}
}

char	*ft_interpret_dollar(t_env *env, char *str)
{
	char	*tmp;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	tmp = NULL;
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (ft_is_dollar(str, i))
		{
			j = j + ft_size_dollar(env, str, i);
			i = ft_moove_index(str, i);
			i--;
		}
		else
			j++;
	}
	if (!ft_malloc_splchar(&tmp, j + 1))
		return (NULL);
	ft_fill_dollar(env, &tmp, str);
	return (tmp);
}

char	**ft_dollar_parse(t_env *env, char **cmd_char)
{
	char	**tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (cmd_char[i])
		i++;
	if (!ft_malloc_dblchar(&tmp, i + 1))
		return (NULL);
	i = -1;
	while (cmd_char[++i])
	{
		tmp[i] = ft_interpret_dollar(env, cmd_char[i]);
		free(cmd_char[i]);
	}
	free(cmd_char);
	return (tmp);
}
