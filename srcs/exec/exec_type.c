/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:18:34 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/27 18:09:58 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_heredoc(t_cmd *cmd)
{
	int		file[2];

	if (pipe(file) < 0)
		return ;
	dup2(file[0], STDIN_FILENO);
	if (!cmd->in_heredoc)
		cmd->in_heredoc = ft_strdup("");
	write(file[1], cmd->in_heredoc, ft_strlen(cmd->in_heredoc));
	close(file[0]);
	close(file[1]);
}

void	exec_redirect(t_cmd *cmd)
{
	int		in;
	int		out;

	if (cmd->in && !cmd->heredoc)
	{
		in = open(cmd->in, O_RDONLY, 0777);
		if (in < 0)
			exit(1);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (cmd->heredoc)
		exec_heredoc(cmd);
	if (cmd->out)
	{
		out = open(cmd->out, O_WRONLY | O_CREAT | (
					O_TRUNC * (cmd->append == 0)) | (
					O_APPEND * (cmd->append > 0)), 0777);
		if (out < 0)
			exit(1);
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

pid_t	exec_single(t_cmd *cmd, t_env **env, int id)
{
	pid_t	pid;

	if (id == 0 && ft_is_builtin(cmd))
	{
		exec_redirect(cmd);
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
	else
	{
		exec_redirect(cmd);
		exec_cmd(cmd, env);
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
		exec_redirect(cmd);
		exec_cmd(cmd, env);
	}
	return (pid);
}

pid_t	exec_type(t_cmd *cmd, t_env **env, int id)
{
	int	pid;

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
