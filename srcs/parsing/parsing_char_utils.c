/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_char_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:51:21 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/22 18:17:11 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_char(char **str, int start, int end)
{
	char	*str1;
	char	*str2;

	str1 = ft_substr(*str, 0, start);
	str2 = ft_substr(*str, end + 1, ft_strlen(*str) - (end + 1));
	free(*str);
	*str = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
}

void	add_char(char **str, int i, char *add)
{
	char	*str1;
	char	*str2;

	str1 = ft_substr(*str, 0, i);
	str2 = ft_substr(*str, i, ft_strlen(*str) - i);
	free(*str);
	*str = ft_strjoin(str1, ft_strjoin(add, str2));
	free(str1);
	free(str2);
}
