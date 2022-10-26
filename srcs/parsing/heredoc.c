/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:38:25 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/26 19:04:24 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(char **final_line, char *heredoc_str)
{
	int		delimiter_found;
	char	*line;
	char	*temp;

	if (*final_line)
		free(*final_line);
	delimiter_found = 1;
	*final_line = ft_strdup("");
	while (delimiter_found)
	{
		line = readline(RED "HEREDOC> " END);
		if (!line)
			break ;
		delimiter_found = ft_strncmp(line, heredoc_str,
				ft_strlen(line) + 1);
		if (delimiter_found)
		{
			temp = ft_strjoin(*final_line, line);
			free(*final_line);
			*final_line = ft_strjoin(temp, "\n");
			free(temp);
		}
		free(line);
	}
	if (find_var(final_line, g_vars.env))
		return (1);
	return (0);
}

/*pid_t	ft_heredoc_fork(char *heredoc_str)
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
	final_line = ft_heredoc(heredoc_str, NULL);
	write(files[1], final_line, ft_strlen(final_line));
	free(final_line);
	return (pid);
}

int	wait_heredoc(char *heredoc_str)
{
	int	status;

	signal(SIGINT, handler_heredoc);
	g_vars.h_pid = ft_heredoc_fork(heredoc_str);
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
}*/
