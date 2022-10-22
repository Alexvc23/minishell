/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:18:34 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/22 17:34:14 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_wait(t_cmd *cmd)
{
	int				status;
	unsigned int	i;

	if (g_vars.n_cmd > 1 || (cmd && !ft_is_builtin(cmd)))
	{
		i = -1;
		while (++i < (unsigned int)g_vars.n_cmd)
			waitpid(g_vars.pids[i], &status, 0);
		if (WIFEXITED(status))
			g_vars.status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			printf("%d\n", WTERMSIG(status));
			g_vars.status = 128 + WTERMSIG(status);
		}
	}
	g_vars.n_cmd = 0;
	free(g_vars.pids);
}

void	exec(void)
{
	int		i;
	t_cmd	*cmd;

	cmd = g_vars.cmd;
	g_vars.n_cmd = ft_cmd_size(g_vars.cmd);
	g_vars.pids = calloc(g_vars.n_cmd, sizeof(int));
	if (!g_vars.n_cmd || !g_vars.pids)
		return ;
	i = 0;
	while (i < g_vars.n_cmd)
	{
		g_vars.pids[i] = exec_type(cmd, &g_vars.env, i);
		if (cmd->next)
			cmd = cmd->next;
		i++;
	}
	update_env(&g_vars.env, ft_strdup("_"),
		ft_strdup(g_vars.cmd->args[g_vars.cmd->n_args - 1]));
	exec_wait(g_vars.cmd);
	dup2(g_vars.stdin, STDIN_FILENO);
	dup2(g_vars.stdout, STDOUT_FILENO);
	dup2(g_vars.stderr, STDERR_FILENO);
}
