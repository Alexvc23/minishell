/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_index_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:52:17 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/09 06:52:43 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	start_c(char *str, int i)
{
	int	start;

	start = i;
	while (str[start] && is_whitespace(str[start]))
		start++;
	return (start);
}

int	end_red(char *str, int start)
{
	int	end;

	end = start;
	while (str[end] && !is_whitespace(str[end])
		&& str[end] != '>' && str[end] != '<')
	{
		if (str[end] == '\'')
			while (str[++end] && str[end] != '\'')
				;
		if (str[end] == '"')
			while (str[++end] && str[end] != '"')
				;
		end++;
	}
	return (end - 1);
}

int	end_arg(char *str, int start)
{
	int	end;

	end = start;
	while (str[end] && !is_whitespace(str[end]))
	{
		if (str[end] == '\'')
			while (str[++end] && str[end] != '\'')
				;
		if (str[end] == '"')
			while (str[++end] && str[end] != '"')
				;
		end++;
	}
	return (end - 1);
}
