/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:38:25 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/27 19:40:49 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_error(char *cmd_str, char *err_str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_str, 2);
	ft_putstr_fd(err_str, 2);
	return (1);
}

int	redirect_output(t_cmd *cmd, int i)
{
	int	is_open;

	is_open = 0;
	if (cmd->rdir_types[i] == RIGHT_SGL_R)
	{
		is_open = open(cmd->files[i], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (cmd->out)
			free(cmd->out);
		cmd->out = ft_strdup(cmd->files[i]);
		cmd->append = 0;
	}
	else if (cmd->rdir_types[i] == RIGHT_DBL_R)
	{
		is_open = open(cmd->files[i], O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (cmd->out)
			free(cmd->out);
		cmd->out = ft_strdup(cmd->files[i]);
		cmd->append = 1;
	}
	if (is_open < 0)
		return (redirect_error(cmd->files[i], ": Permission denied\n"));
	if (is_open != 0)
		close(is_open);
	return (0);
}

int	redirect_input(t_cmd *cmd, int i)
{
	int	is_open;

	is_open = 0;
	if (cmd->rdir_types[i] == LEFT_SGL_R)
	{
		is_open = open(cmd->files[i], O_RDONLY);
		if (cmd->in)
			free(cmd->in);
		cmd->in = ft_strdup(cmd->files[i]);
		cmd->heredoc = 0;
	}
	else if (cmd->rdir_types[i] == LEFT_DBL_R)
		cmd->heredoc = 1;
	if (is_open < 0)
		return (redirect_error(cmd->files[i], ": No such file or directory\n"));
	if (is_open != 0)
		close(is_open);
	return (0);
}

int	test_redirect(void)
{
	int		i;
	t_cmd	*cmd;

	print_com(g_vars.cmd);
	cmd = g_vars.cmd;
	while (cmd)
	{
		if (make_in_heredoc(cmd))
			return (1);
		i = 0;
		while (i < cmd->n_rdirs)
		{
			if (redirect_output(cmd, i)
				|| redirect_input(cmd, i))
				return (1);
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}
