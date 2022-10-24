/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:45:43 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/24 15:38:18 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_var(char **str, int start, int end, t_env *env)
{
	char	*var;

	var = ft_substr(*str, start + 1, end - start);
	remove_char(str, start, end);
	while (env)
	{
		if (!ft_strncmp(var, env->key, ft_strlen(var) + 1))
		{
			add_char(str, start, env->value);
			break ;
		}
		env = env->next;
	}
	free(var);
}

int	check_var(char **str, int *i, t_env *env)
{
	int	start;

	if ((*str)[*i] == '$')
	{
		start = *i;
		(*i)++;
		if ((*str)[*i] == '?')
		{
			remove_char(str, start, *i);
			add_char(str, start, ft_itoa(g_vars.status));
			return (0);
		}
		while ((*str)[*i] && (ft_isalnum((*str)[*i]) || (*str)[*i] == '_'))
			(*i)++;
		replace_var(str, start, *i - 1, env);
		*i = start;
	}
	return (0);
}

int	find_var(char **str, t_env *env)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
			while ((*str)[++i] != '\'')
				;
		if ((*str)[i] == '"')
			while ((*str)[++i] != '"')
				if (check_var(str, &i, env))
					return (1);
		if (check_var(str, &i, env))
			return (1);
		i++;
	}
	return (0);
}

void	replace_tild(char **str, int start, t_env *env)
{
	if ((*str)[start] && (*str)[start] == '~')
	{
		if ((*str)[start + 1] && (*str)[start + 1] == '/')
		{
			remove_char(str, start, start);
			while (env)
			{
				if (!ft_strncmp("HOME", env->key, ft_strlen("HOME") + 1))
				{
					add_char(str, start, env->value);
					break ;
				}
				env = env->next;
			}
		}
	}
}

int	find_tild(char **str, t_env *env)
{
	int	i;

	i = 0;
	replace_tild(str, 0, env);
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
			while ((*str)[++i] != '\'')
				;
		if ((*str)[i] == '"')
			while ((*str)[++i] != '"')
				;
		if ((*str)[i] && is_whitespace((*str)[i]) && (*str)[i + 1])
			replace_tild(str, i + 1, env);
		i++;
	}
	return (0);
}
