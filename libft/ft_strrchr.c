/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:37:54 by abouchet          #+#    #+#             */
/*   Updated: 2021/11/20 16:41:10 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	long	len;

	len = ft_strlen(s);
	while (len >= 0 && s[len] != (char)c)
		len--;
	if (len < 0)
		return (0);
	return ((char *)s + len);
}
