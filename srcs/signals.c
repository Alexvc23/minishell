/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:10:08 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/24 14:37:48 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		if (g_vars.h_pid)
			kill(g_vars.h_pid, 15);
		write(1, "\n", 1);
	}
}

void	handler_shell(int sig)
{
	if (g_vars.n_cmd > 0)
		return ;
	if (sig == SIGINT)
	{
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT && g_vars.h_pid == 0)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
