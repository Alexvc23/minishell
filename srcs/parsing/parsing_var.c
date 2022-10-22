/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:45:43 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/22 18:18:09 by abouchet         ###   ########lyon.fr   */
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