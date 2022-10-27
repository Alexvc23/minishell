/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:38:25 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/27 21:40:03 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_fd(int fd)
{
	char	*final_str;
	char	*tmp;
	char	*str;

	final_str = NULL;
	str = get_next_line(fd);
	while (str)
	{
		if (!final_str)
			final_str = ft_strdup("");
		tmp = ft_strjoin(final_str, str);
		free(final_str);
		final_str = ft_strdup(tmp);
		free(tmp);
		free(str);
		str = get_next_line(fd);
	}
	return (final_str);
}

int	ft_heredoc(char **final_line, char *heredoc_str)
{
	char	*line;
	char	*temp;

	*final_line = ft_strdup("");
	while (1)
	{
		ft_termios();
		line = readline(RED "HEREDOC> " END);
		reset_termios();
		if (!line || !ft_strncmp(line, heredoc_str, ft_strlen(line) + 1))
			break ;
		temp = ft_strjoin(*final_line, line);
		free(*final_line);
		*final_line = ft_strjoin(temp, "\n");
		free(temp);
	}
	if (line)
		free(line);
	return (0);
}

int	wait_heredoc(t_cmd *cmd, char *heredoc_str)
{
	int	status;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (1);
	g_vars.h_pid = fork();
	if (g_vars.h_pid == -1)
		return (1);
	else if (g_vars.h_pid == 0)
	{
		close(pipefd[0]);
		ft_heredoc(&(cmd->in_heredoc), heredoc_str);
		write(pipefd[1], cmd->in_heredoc, ft_strlen(cmd->in_heredoc));
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	if (wait(&status) < 0)
		kill(g_vars.h_pid, SIGTERM);
	g_vars.h_pid = 0;
	close(pipefd[1]);
	cmd->in_heredoc = read_fd(pipefd[0]);
	close(pipefd[0]);
	if (WIFSIGNALED(status))
		return (1);
	return (0);
}

int	make_in_heredoc(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->n_rdirs)
	{
		if (cmd->rdir_types[i] == LEFT_DBL_R)
		{
			if (cmd->in_heredoc)
				free(cmd->in_heredoc);
			if (wait_heredoc(cmd, cmd->files[i]))
				return (1);
			if (cmd->in_heredoc)
				if (find_var(&(cmd->in_heredoc), g_vars.env))
					return (1);
		}
		i++;
	}
	return (0);
}
