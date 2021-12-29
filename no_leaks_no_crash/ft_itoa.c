/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachin <nachin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:31:26 by nachin            #+#    #+#             */
/*   Updated: 2021/12/21 18:37:12 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_intlen(int nb)
{
	int	lenght;

	lenght = 0;
	if (nb == 0)
		return (1);
	else if (nb < 0)
	{
		nb = nb * (-1);
		lenght++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		lenght++;
	}
	return (lenght);
}

static char	*ft_imtoa(char **ret)
{
	if (!ft_malloc_splchar(ret, 12))
		return (NULL);
	(*ret)[0] = '-';
	(*ret)[1] = '2';
	(*ret)[2] = '1';
	(*ret)[3] = '4';
	(*ret)[4] = '7';
	(*ret)[5] = '4';
	(*ret)[6] = '8';
	(*ret)[7] = '3';
	(*ret)[8] = '6';
	(*ret)[9] = '4';
	(*ret)[10] = '8';
	return (*ret);
}

char	*ft_itoa(int nb)
{
	char	*ret;
	int		lenght;
	int		sign;

	if (nb == -2147483648)
		return (ft_imtoa(&ret));
	lenght = ft_intlen(nb);
	sign = 0;
	if (!ft_malloc_splchar(&ret, lenght + 1))
		return (NULL);
	if (nb < 0)
	{
		nb = nb * (-1);
		sign = 1;
	}
	while (--lenght >= 0)
	{
		ret[lenght] = ((nb % 10) + 48);
		nb = nb / 10;
	}
	if (sign == 1)
		ret[0] = '-';
	return (ret);
}
