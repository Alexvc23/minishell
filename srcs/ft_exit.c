/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:25:13 by fdevigne          #+#    #+#             */
/*   Updated: 2022/10/11 08:53:40 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 
https://www.gnu.org/software/bash/manual/bash.html#Bourne-Shell-Builtins
*/

static int	str_is_valid_num(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] || !ft_isdigit(str[i - 1]) || i > 19)
		return (0);
	return (1);
}

int	ft_exit(t_cmd *cmd)
{
	int	exit_status;

	ft_putstr_fd("exit\n", 1);
	//exit_status = g_vars.status;
	if (cmd && cmd->n_args >= 2 && !str_is_valid_num(cmd->args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_status = 255;
	}
	else if (cmd && cmd->n_args > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit_status = 1;
	}
	else if (cmd && cmd->n_args == 2)
		exit_status = ft_atoi(cmd->args[0]) % 256;
	else
		exit_status = 0;
	//reset_terminal(g_vars);
	free(g_vars.pids);
	free_commands(&g_vars.cmd);
	free_envs(&g_vars.env);
	exit(exit_status);
}
