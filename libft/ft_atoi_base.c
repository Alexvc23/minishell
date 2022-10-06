/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 06:36:39 by abouchet          #+#    #+#             */
/*   Updated: 2022/03/21 06:43:52 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_is_sign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

static int	c_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	c_is_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	long int		retour;
	unsigned int	i;
	int				valeur_c;
	int				sign;

	retour = 0;
	i = 0;
	sign = 1;
	while (c_is_space(str[i]) == 1)
		i++;
	if (c_is_sign(str[i]) == 1)
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (c_is_in_base(str[i], base) != -1)
	{
		valeur_c = c_is_in_base(str[i], base);
		retour = retour * ft_strlen(base) + valeur_c;
		i++;
	}
	return (retour * sign);
}
