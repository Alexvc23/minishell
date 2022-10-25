/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 21:37:59 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/25 17:53:00 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_errors(t_cmd *cmd)
{
	if (cmd->n_args > 1 && cmd->args[1][0] == '-')
	{
		ft_putstr_fd("env: No options handled\n", 2);
		return (1);
	}
	else if (cmd->n_args > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	return (0);
}

/* print environement variables stored in t_env struct*/
int	ft_env(t_cmd *cmd, t_env **env)
{
	t_env	*tmp;
	int		err_status;

	err_status = check_errors(cmd);
	if (err_status)
		return (err_status);
	if (!env)
		return (1);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "_", 2))
			printf("%s=%s\n", tmp->key, "/usr/bin/env");
		else
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
