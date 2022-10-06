/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:11:05 by abouchet          #+#    #+#             */
/*   Updated: 2021/11/20 16:47:48 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nblen(long int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*nb;
	size_t		i;
	long int	nbr;

	nbr = n;
	i = ft_nblen(nbr);
	if (nbr == 0)
		i = 1;
	nb = malloc(sizeof(char) * (i + 1));
	if (!nb)
		return (NULL);
	nb[i--] = '\0';
	if (nbr < 0)
	{
		nb[0] = '-';
		nbr = -nbr;
	}
	else if (nbr == 0)
		nb[0] = '0';
	while (nbr != 0)
	{
		nb[i--] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (nb);
}
