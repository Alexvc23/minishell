/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 21:37:59 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/11 08:51:03 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* print environement variables stored in t_env struct*/
int	ft_env(t_cmd *cmd, t_env **env)
{
	t_env	*tmp;

	if (cmd->n_args > 1 && cmd->args[1][0] == '-')
	{
		ft_putstr_fd("pwd: No options handled\n", 2);
		return (1);
	}
	else if (cmd->n_args > 1)
	{
		ft_putstr_fd("pwd: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	tmp = *env;
	if (!env)
		return (1);
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
