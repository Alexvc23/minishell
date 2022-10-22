/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:38:25 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/22 18:16:56 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_heredoc(t_cmd *cmd, char *final_line)
{
	int		delimiter_found;
	char	*line;
	char	*temp;

	delimiter_found = 1;
	final_line = ft_strdup("");
	while (delimiter_found)
	{
		line = readline(RED "HEREDOC> " END);
		if (!line)
			break ;
		delimiter_found = ft_strncmp(line, cmd->files[cmd->n_rdirs - 1],
				ft_strlen(line) + 1);
		if (delimiter_found)
		{
			temp = ft_strjoin(final_line, line);
			free(final_line);
			final_line = ft_strjoin(temp, "\n");
			free(temp);
		}
		free(line);
	}
	find_var(&final_line, g_vars.env);
	return (final_line);
}

pid_t	ft_heredoc_fork(t_cmd *cmd)
{
	pid_t	pid;
	int		files[2];
	char	*final_line;

	dup2(g_vars.stdin, STDIN_FILENO);
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
		return (pid);
	}
	final_line = ft_heredoc(cmd, NULL);
	write(files[1], final_line, ft_strlen(final_line));
	free(final_line);
	return (pid);
}

int	wait_heredoc(t_cmd *cmd)
{
	int	status;

	signal(SIGINT, handler_heredoc);
	g_vars.h_pid = ft_heredoc_fork(cmd);
	if (g_vars.h_pid == 0)
		exit(0);
	waitpid(g_vars.h_pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_vars.status = WEXITSTATUS(status);
		return (status);
	}
	else if (WIFSIGNALED(status))
	{
		g_vars.status = 2;
		return (7);
	}
	return (0);
}
