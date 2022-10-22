/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:10:08 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/22 17:40:28 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		if (g_vars.h_pid)
			kill(g_vars.h_pid, 15);
	}
}

void	handler_shell(int sig)
{
	if (sig == SIGINT)
	{
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "\n", 1);
	}
	rl_on_new_line();
	rl_redisplay();
}
