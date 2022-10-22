/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:18:34 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/22 18:15:32 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->com, "echo", ft_strlen("echo") + 1))
		return (1);
	if (!ft_strncmp(cmd->com, "export", ft_strlen("export") + 1))
		return (1);
	if (!ft_strncmp(cmd->com, "unset", ft_strlen("unset") + 1))
		return (1);
	if (!ft_strncmp(cmd->com, "env", ft_strlen("env") + 1))
		return (1);
	if (!ft_strncmp(cmd->com, "pwd", ft_strlen("pwd") + 1))
		return (1);
	if (!ft_strncmp(cmd->com, "cd", ft_strlen("cd") + 1))
		return (1);
	if (!ft_strncmp(cmd->com, "exit", ft_strlen("exit") + 1))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_env **env)
{
	if (!ft_strncmp(cmd->com, "exit", ft_strlen("exit") + 1))
		return (ft_exit(cmd));
	else if (!ft_strncmp(cmd->com, "echo", ft_strlen("echo") + 1))
		return (ft_echo(cmd));
	else if (!ft_strncmp(cmd->com, "export", ft_strlen("export") + 1))
		return (ft_export(cmd, env));
	else if (!ft_strncmp(cmd->com, "unset", ft_strlen("unset") + 1))
		return (ft_unset(cmd, env));
	else if (!ft_strncmp(cmd->com, "env", ft_strlen("env") + 1))
		return (ft_env(cmd, env));
	else if (!ft_strncmp(cmd->com, "pwd", ft_strlen("pwd") + 1))
		return (ft_pwd(cmd, env));
	else if (!ft_strncmp(cmd->com, "cd", ft_strlen("cd") + 1))
		return (ft_cd(cmd, env));
	return (1);
}
