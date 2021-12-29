/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/28 10:38:47 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*the function ft_split_env_p is used to create a list t_env 
which will be the environnement of our minishell
it takes as argument the argument from the main envp directly
and returns the first element of the list
which will contain name and value from envp[0]
(we add new element at the end of the list so we conserv the order of envp)
the function return a list that you will have 
to free before the end of your program*/

int	ft_env(t_env *env, char **argv)
{
	if (argv[1] != NULL)
	{
		g_exit_status = 1;
		write(2, "env: arguments or options are not suported\n", 43);
		return (1);
	}
	else
	{
		ft_print_list_env(env);
		g_exit_status = 0;
		return (0);
	}
}

char	**ft_tenv_to_envp(t_env *env)
{
	t_env	*tmp;
	char	**ret;
	int		size;
	int		i;
	int		j;

	if (!env)
		return (NULL);
	size = ft_size_list_env(env);
	if (ft_malloc_dblchar(&ret, size + 1))
		return (NULL);
	tmp = env;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (tmp->name[++j])
			ret[i] = ft_realloc(&ret[i], tmp->name[j]);
		ret[i] = ft_realloc(&ret[i], '=');
		j = -1;
		while (tmp->value[++j])
			ret[i] = ft_realloc(&ret[i], tmp->value[j]);
		tmp = tmp->nxt;
	}
	return (ret);
}

t_env	*ft_envp_to_tenv(char **env_p)
{
	t_env	*ret;
	char	*name;
	char	*value;
	int		i;
	int		j;

	ret = NULL;
	name = NULL;
	value = NULL;
	i = -1;
	while (env_p[++i])
	{
		j = -1;
		while (env_p[i][++j] != '=')
			name = ft_realloc(&name, env_p[i][j]);
		while (env_p[i][++j])
			value = ft_realloc(&value, env_p[i][j]);
		if (name)
			ret = ft_eadd_tolist_env(ret, name, value);
		name = NULL;
		value = NULL;
	}
	return (ret);
}
