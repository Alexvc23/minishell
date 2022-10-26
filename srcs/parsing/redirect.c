/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:38:25 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/26 19:30:21 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_output(t_cmd *cmd, int i)
{
	int	is_open;

	is_open = 0;
	if (cmd->rdir_types[i] == RIGHT_SGL_R)
	{
		is_open = open(cmd->files[i], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		cmd->out = ft_strdup(cmd->files[i]);
		cmd->append = 0;
	}
	else if (cmd->rdir_types[i] == RIGHT_DBL_R)
	{
		is_open = open(cmd->files[i], O_WRONLY | O_APPEND | O_CREAT, 0777);
		cmd->out = ft_strdup(cmd->files[i]);
		cmd->append = 1;
	}
	if (is_open < 0)
	{
		ft_putstr_fd(cmd->files[i], 2);
		ft_putstr_fd(" : Cannot access file or directory\n", 2);
		return (1);
	}
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
		cmd->in = ft_strdup(cmd->files[i]);
		cmd->heredoc = 0;
	}
	else if (cmd->rdir_types[i] == LEFT_DBL_R)
		cmd->heredoc = 1;
	if (is_open < 0)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(cmd->files[i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (is_open != 0)
		close(is_open);
	return (0);
}

int	test_redirect(void)
{
	int		i;
	t_cmd	*cmd;

	cmd = g_vars.cmd;
	while (cmd)
	{
		i = 0;
		while (i < cmd->n_rdirs)
		{
			if (cmd->rdir_types[i] == LEFT_DBL_R)
				if (ft_heredoc(&(cmd->in_heredoc), cmd->files[i]))
					return (1);
			i++;
		}
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
