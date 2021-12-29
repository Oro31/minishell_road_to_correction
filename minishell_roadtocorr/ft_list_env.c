/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:05:31 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/26 08:07:11 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*this function is used to add a new element at the top
of a list of type t_env, it returns the pointer to this new element*/

t_env	*ft_hadd_tolist_env(t_env *list, char *name, char *value)
{
	t_env	*newelem;

	newelem = malloc(sizeof(t_env));
	if (!newelem)
	{
		perror("malloc failed");
		return (NULL);
	}
	newelem->name = name;
	newelem->value = value;
	newelem->nxt = list;
	return (newelem);
}

/*this function is used to add a new element at the end
of a list of type t_env, it returns the pointer to the head of the list*/

t_env	*ft_eadd_tolist_env(t_env *list, char *name, char *value)
{
	t_env	*newelem;
	t_env	*tmp;

	newelem = malloc(sizeof(t_env));
	if (!newelem)
	{
		perror("malloc failed");
		return (NULL);
	}
	newelem->name = name;
	newelem->value = value;
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

t_env	*ft_ndelete_env(t_env *list, int n)
{
	t_env	*tmp;
	t_env	*ptmp;
	int		i;

	if (!list)
		return (NULL);
	tmp = list;
	ptmp = list->nxt;
	i = 0;
	while (++i < n && tmp)
	{
		ptmp = tmp;
		tmp = tmp->nxt;
	}
	if (!tmp)
		return (list);
	ptmp->nxt = tmp->nxt;
	if (tmp->name)
		free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
	if (n == 1)
		return (ptmp);
	return (list);
}

/*this function is used to free all elements of a listof type t_env
everything that were allocated in each element are freed*/

void	ft_free_list_env(t_env **list)
{
	t_env	*tmp;

	if (list)
	{
		if (*list)
		{
			while (*list)
			{
				tmp = (*list)->nxt;
				free((*list)->name);
				free((*list)->value);
				(*list)->name = NULL;
				(*list)->value = NULL;
				free(*list);
				*list = NULL;
				*list = tmp;
			}
		}
	}
}
