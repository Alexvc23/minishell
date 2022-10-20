/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:38:25 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/20 20:14:51 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//need to change it for arthur parsing

void	ft_heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_vars.h_pid)
			kill(g_vars.h_pid, 15);
	}
}

char	*ft_set_s(char *line, char *previous, int isInquote)
{
	char	*temp;
	char	*final;
	char	*temp2;

	temp2 = NULL;
	temp = NULL;
	final = NULL;
	if (isInquote == 0)
	{
		//temp2 = ft_with_var(line, NULL, NULL, 0); //ft?
		temp = ft_strjoin(temp2, "\n");
	}
	else
		temp = ft_strjoin(line, "\n");
	if (previous)
		final = ft_strjoin(previous, temp);
	else
		final = ft_strdup(temp);
	free(temp);
	if (temp2)
		free(temp2);
	if (previous)
		free(previous);
	return (final);
}

int	ft_quote_in_heredoc(char *end)
{
	int	i;

	i = 0;
	while (end[i])
	{
		if (end[i] == '\'' || end[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	ft_bool_heredoc(char **end, int i, int *bool_quote, char **result)
{
	if (!end[i] && !*result)
		*result = ft_strdup("");
	if (end[i])
		*bool_quote = ft_quote_in_heredoc(end[i]);
	else
		*bool_quote = 0;
}

char	*ft_heredoc(char **end, t_cmd *stru, char *final_line)
{
	int		i;
	int		bool_quote;
	char	*line;
	char	*temp;

	i = 0;
	while (end[i])
	{
		line = readline("\033[31mHEREDOC\033[0m> ");
		if (!line)
			break ;
		//temp = ft_gro_quotes(end[i]); //ft?
		temp = NULL;
		if (!ft_strncmp(line, temp, ft_strlen(line) + 1))
			i++;
		ft_bool_heredoc(end, i, &bool_quote, &final_line);
		if (end[i])
			final_line = ft_set_s(line, final_line, bool_quote);
		free(line);
		free(temp);
	}
	//freetab(end);
	end = NULL;
	stru->heredoc = 0;
	return (final_line);
}

static void ft_heredoc_child(char **end, t_cmd *stru, int files[2])
{
	char	*final_line;

	final_line = NULL;
	final_line = ft_heredoc(end, stru, NULL);
	write(files[1], final_line, ft_strlen(final_line));
	if (final_line)
		free(final_line);
}

pid_t ft_heredoc_fork(char **end, t_cmd *stru)
{
	pid_t	pid;
	int		files[2];

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
	ft_heredoc_child(end, stru, files);
	return (pid);
}

int wait_heredoc(char **end, t_cmd *stru)
{
	int	status;

	signal(SIGINT, ft_heredoc_handler);
	g_vars.h_pid = ft_heredoc_fork(end, stru);
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
