/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:33:23 by fdevigne          #+#    #+#             */
/*   Updated: 2022/10/22 18:16:51 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_valid_key(char *key)
{
	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (*(++key))
	{
		if (!ft_isalpha(*key) && !ft_isdigit(*key) && *key != '_')
		{
			if (*key == '=')
				return (1);
			return (0);
		}
	}
	return (1);
}

// Before unsetting the variable, where making sure that
// It's name (the key) is a valid one

static void	ft_freeone_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

// The actual deletion of the variable(s)

static void	ft_del_env(t_env **env, char *key)
{
	t_env	*before;
	t_env	*tmp;

	before = NULL;
	tmp = *env;
	while (tmp && !ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
	{
		before = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	if (!before)
	{
		*env = tmp->next;
		ft_freeone_env(tmp);
		return ;
	}
	before->next = tmp->next;
	ft_freeone_env(tmp);
}

int	ft_unset(t_cmd *cmd, t_env **env)
{
	char	*key;

	if (cmd->n_args == 1)
		return (0);
	key = cmd->args[1];
	if (!ft_is_valid_key(key))
	{
		ft_putstr_fd("Invalid key name.\n", 1);
		return (1);
	}
	ft_del_env(env, key);
	return (0);
}
