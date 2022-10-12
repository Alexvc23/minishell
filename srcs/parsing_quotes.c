/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:49:42 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/11 04:35:00 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quotes(char	**str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			remove_char(str, i, i);
			while ((*str)[i] != '\'')
				i++;
			remove_char(str, i, i);
		}
		if ((*str)[i] == '"')
		{
			remove_char(str, i, i);
			while ((*str)[i] != '"')
				i++;
			remove_char(str, i, i);
			i--;
		}
		i++;
	}
}
