/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:36:21 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/22 18:17:24 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*last_env(t_env *env)
{
	if (env == 0)
		return (0);
	while (env->next != 0)
		env = env->next;
	return (env);
}

void	add_back_env(t_env **envs, t_env *new)
{
	t_env	*last;

	if (*envs == NULL)
		*envs = new;
	else
	{
		last = last_env(*envs);
		last->next = new;
	}
}

int	new_env(char *str, t_env **envs)
{
	int		equal;
	t_env	*new_elem;

	new_elem = malloc(sizeof(t_env));
	if (!new_elem)
		return (error_parsing("Malloc Error\n", 2));
	equal = 0;
	while (str[equal] && str[equal] != '=')
		equal++;
	new_elem->key = ft_substr(str, 0, equal);
	new_elem->value = ft_substr(str, equal + 1, ft_strlen(str) - (equal + 1));
	new_elem->next = NULL;
	add_back_env(envs, new_elem);
	return (0);
}

int	create_envs(char **envp, t_env **envs)
{
	int	i;

	*envs = NULL;
	i = 0;
	while (envp[i])
	{
		if (new_env(envp[i], envs))
			return (1);
		i++;
	}
	return (0);
}
