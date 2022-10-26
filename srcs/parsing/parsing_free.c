/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:32:46 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/26 19:31:30 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

void	free_commands(t_cmd **commands)
{
	t_cmd	*temp;

	while (*commands)
	{
		temp = (*commands)->next;
		if ((*commands)->com)
			free((*commands)->com);
		if ((*commands)->n_args)
			free_tab((*commands)->args, (*commands)->n_args);
		if ((*commands)->n_rdirs)
		{
			free((*commands)->rdir_types);
			free_tab((*commands)->files, (*commands)->n_rdirs);
		}
		if ((*commands)->in)
			free((*commands)->in);
		if ((*commands)->in_heredoc)
			free((*commands)->in_heredoc);
		if ((*commands)->out)
			free((*commands)->out);
		free(*commands);
		*commands = temp;
	}
}

void	free_envs(t_env **envs)
{
	t_env	*temp;

	while (*envs)
	{
		temp = (*envs)->next;
		if ((*envs)->key)
			free((*envs)->key);
		if ((*envs)->value)
			free((*envs)->value);
		free(*envs);
		*envs = temp;
	}
}

int	error_parsing(char *err_str, int fd)
{
	free_commands(&g_vars.cmd);
	ft_putstr_fd(err_str, fd);
	return (1);
}
