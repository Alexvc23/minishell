/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:40:01 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/26 18:38:13 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_command(t_cmd *new_cmd)
{
	new_cmd->com = NULL;
	new_cmd->n_args = 0;
	new_cmd->args = NULL;
	new_cmd->n_rdirs = 0;
	new_cmd->rdir_types = NULL;
	new_cmd->files = NULL;
	new_cmd->in = NULL;
	new_cmd->in_heredoc = NULL;
	new_cmd->out = NULL;
	new_cmd->heredoc = 0;
	new_cmd->append = 0;
	new_cmd->next = NULL;
}
