/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:00:58 by abouchet          #+#    #+#             */
/*   Updated: 2021/11/20 17:30:50 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_tab(char **tab)
{
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	free(tab);
}

static char	*cpy_in_tab(char *dest, char const *src, int *i, int *j)
{
	int	k;

	k = 0;
	while (k < *j - *i)
	{
		dest[k] = src[k];
		k++;
	}
	dest[k] = '\0';
	*i = *j;
	return (dest);
}

static char	**malloc_tab(char const *s, char c, int *word)
{
	int		i;
	int		size;
	char	**tab;
	int		j;

	*word = 0;
	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		j = i;
		while (s[j] != c && s[j] != '\0')
			j++;
		if (j == i)
			break ;
		size++;
		i = j;
	}
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

static int	find_start_last(char const *s, char c, int *i, int *j)
{
	while (s[(*i)] == c && s[(*i)] != '\0')
		(*i)++;
	*j = *i;
	while (s[(*j)] != c && s[(*j)] != '\0')
		(*j)++;
	if (*j == *i)
		return (1);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		word;
	char	**tab;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	tab = malloc_tab(s, c, &word);
	if (!tab)
		return (NULL);
	while (s[i] != '\0')
	{
		if (find_start_last(s, c, &i, &j) == 1)
			break ;
		tab[word] = malloc(sizeof(char) * (j - i + 1));
		if (!tab[word])
		{
			free_tab(tab);
			return (NULL);
		}
		cpy_in_tab(tab[word++], &s[i], &i, &j);
	}
	tab[word] = 0;
	return (tab);
}
