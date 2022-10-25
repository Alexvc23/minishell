/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:33:23 by fdevigne          #+#    #+#             */
/*   Updated: 2022/10/25 14:57:59 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_valid_key(char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 0;
	while (key[i])
	{
		if (!ft_isalpha(key[i]) && !ft_isdigit(key[i]) && key[i] != '_')
			return (0);
		i++;
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
	while (tmp && ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
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
	int		i;
	int		valid;

	valid = 1;
	i = 1;
	while (cmd->args[i])
	{
		if (!ft_is_valid_key(cmd->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 1);
			ft_putstr_fd(cmd->args[i], 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			valid = 0;
		}
		i++;
	}
	if (!valid)
		return (1);
	i = 1;
	while (cmd->args[i])
	{
		ft_del_env(env, cmd->args[i]);
		i++;
	}
	return (0);
}
