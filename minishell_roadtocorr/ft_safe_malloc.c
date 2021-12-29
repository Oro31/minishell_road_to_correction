/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:36:10 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/21 18:13:02 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*those functions are a way to use malloc in a safe way
they return 0 in case of failure and put a message in stderr
they return 1 in case of succes
except ft_malloc_splint those functions put an end identifier at the end
so be aware of the size you'r giving to them*/

int	ft_malloc_dblchar(char ***tmp, int size)
{
	*tmp = malloc(sizeof(char *) * size);
	if (!*tmp)
	{
		perror("malloc failed");
		return (0);
	}
	(*tmp)[size - 1] = NULL;
	return (1);
}

int	ft_malloc_splchar(char **tmp, int size)
{
	*tmp = malloc(sizeof(char) * size);
	if (!*tmp)
	{
		perror("malloc failed");
		return (0);
	}
	(*tmp)[size - 1] = '\0';
	return (1);
}

int	ft_malloc_dblint(int ***tmp, int size)
{
	*tmp = malloc(sizeof(int *) * size);
	if (!*tmp)
	{
		perror("malloc failed");
		return (0);
	}
	(*tmp)[size - 1] = NULL;
	return (1);
}

int	ft_malloc_splint(int **tmp, int size)
{
	*tmp = malloc(sizeof(int) * size);
	if (!*tmp)
	{
		perror("malloc failed");
		return (0);
	}
	return (1);
}
