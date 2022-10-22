/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:18:34 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/22 18:15:57 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_redirec(t_cmd *cmd)
{
	int	in;
	int	out;

	if (cmd->in && !cmd->heredoc)
	{
		in = open(cmd->in, O_RDONLY, 0777);
		if (in < 0)
			exit(1);
		dup2(in, STDIN_FILENO);
		close(in);
	}
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
