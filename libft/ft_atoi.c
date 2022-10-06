/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:18:27 by abouchet          #+#    #+#             */
/*   Updated: 2022/03/21 06:35:54 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_is_numeric(char c)
{
	if (c >= '0' && '9' >= c)
		return (1);
	return (0);
}

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

int	ft_atoi(const char *str)
{
	int				retour;
	unsigned int	i;
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
	while (c_is_numeric(str[i]) == 1)
	{
		retour = retour * 10 + str[i] - '0';
		i++;
	}
	return (retour * sign);
}
