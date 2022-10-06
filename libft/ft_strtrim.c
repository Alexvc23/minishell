/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:15:02 by abouchet          #+#    #+#             */
/*   Updated: 2021/11/23 12:21:01 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_c_in_str(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static size_t	ft_strlen_start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[j] && ft_c_in_str(set, s1[j]))
	{
		if (ft_c_in_str(set, s1[j]))
			i++;
		j++;
	}
	return (i);
}

static size_t	ft_strlen_end(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(s1) - 1;
	while (j >= 0 && ft_c_in_str(set, s1[j]))
	{
		if (ft_c_in_str(set, s1[j]))
			i++;
		j--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	size_t			len_start;
	size_t			len_end;
	unsigned int	i;

	if (!s1 || !set)
		return (NULL);
	len_start = ft_strlen_start(s1, set);
	len_end = ft_strlen_end(s1, set);
	if (len_end == ft_strlen(s1))
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) - len_end - len_start + 1));
	if (!str)
		return (NULL);
	i = len_start - 1;
	while (++i < ft_strlen(s1) - len_end)
		str[i - len_start] = s1[i];
	str[i - len_start] = '\0';
	return (str);
}
