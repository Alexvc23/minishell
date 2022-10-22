/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:18:34 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/22 18:15:50 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	exec_single(t_cmd *cmd, t_env **env, int id)
{
	pid_t	pid;

	if (id == 0 && ft_is_builtin(cmd))
	{
		dup_redirec(cmd);
		g_vars.status = exec_builtin(cmd, env);
		dup2(g_vars.stdin, STDIN_FILENO);
		dup2(g_vars.stderr, STDERR_FILENO);
		dup2(g_vars.stdout, STDOUT_FILENO);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid)
		return (pid);
	dup_redirec(cmd);
	exec_cmd(cmd, env);
	return (pid);
}

pid_t	exec_heredoc(t_cmd *cmd)
{
	pid_t	pid;
	int		file[2];

	if (pipe(file) < 0)
		return (-1);
	pid = fork();
	if (pid)
	{
		dup2(file[0], STDIN_FILENO);
		close(file[0]);
		close(file[1]);
	}
	else
	{
		if (!cmd->in)
			cmd->in = ft_strdup("");
		pid = write(file[1], cmd->in, ft_strlen(cmd->in));
		close(file[0]);
		close(file[1]);
		exit(pid);
	}
	return (pid);
}

pid_t	exec_pipe(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	int		files[2];

	if (pipe(files) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid)
	{
		dup2(files[0], STDIN_FILENO);
		close(files[0]);
		close(files[1]);
	}
	else
	{
		dup2(files[1], STDOUT_FILENO);
		close(files[0]);
		close(files[1]);
		dup_redirec(cmd);
		exec_cmd(cmd, env);
	}
	return (pid);
}

pid_t	exec_type(t_cmd *cmd, t_env **env, int id)
{
	int	pid;

	if (cmd->heredoc)
		pid = exec_heredoc(cmd);
	if (!cmd->next)
	{
		dup2(g_vars.stdout, STDOUT_FILENO);
		pid = exec_single(cmd, env, id);
		dup2(g_vars.stdin, STDIN_FILENO);
	}
	else
		pid = exec_pipe(cmd, env);
	return (pid);
}
