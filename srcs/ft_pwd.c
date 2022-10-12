/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:08:07 by fdevigne          #+#    #+#             */
/*   Updated: 2022/10/11 08:55:27 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Print current location in the system.

int	ft_pwd(t_cmd *cmd, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!env)
		return (1);
	if (cmd->n_args > 1 && cmd->args[1][0] == '-')
	{
		ft_putstr_fd("pwd: No options handled\n", 2);
		return (1);
	}
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 3))
		{
			printf("%s\n", tmp->value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
