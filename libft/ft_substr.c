/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:58:54 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/02 06:32:33 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	end;
	char			*str;

	if (!s)
		return (NULL);
	end = 0;
	while (end < start + len && s[end])
		end++;
	if (start > end)
		start = end;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	i = start;
	while (i < end)
	{
		str[i - start] = s[i];
		i++;
	}
	str[i - start] = '\0';
	return (str);
}
