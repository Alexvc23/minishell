/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:10:08 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/28 03:26:10 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		kill(g_vars.h_pid, SIGTERM);
		g_vars.status = 1;
		write(1, "\n", 1);
	}
}

static void	handler_standard(int sig)
{
	if (g_vars.n_cmd > 0)
		return ;
	if (sig == SIGINT)
	{
		g_vars.status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT && g_vars.h_pid == 0)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler_shell(int sig)
{
	if (g_vars.h_pid == 0)
		handler_standard(sig);
	else
		handler_heredoc(sig);
}

void	handler_cmd(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("minishell: Quit: 3\n", 1);
		g_vars.status = 131;
	}
	else if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_vars.status = 130;
	}
}
