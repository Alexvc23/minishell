/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:43:48 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/23 16:08:05 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redirections(char *str)
{
	int	i;
	int	nb_redirections;

	nb_redirections = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == '"')
			while (str[++i] && str[i] != '"')
				;
		if ((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<'))
		{
			i++;
			nb_redirections++;
		}
		else if (str[i] == '>' || str[i] == '<')
			nb_redirections++;
		i++;
	}
	return (nb_redirections);
}

void	find_replace_tild(char **str, t_env *env)
{
	if ((*str)[0] && (*str)[0] == '~')
	{
		if ((*str)[1] && (*str)[1] == '/')
		{
			remove_char(str, 0, 0);
			while (env)
			{
				if (!ft_strncmp("HOME", env->key, ft_strlen("HOME") + 1))
				{
					add_char(str, 0, env->value);
					break ;
				}
				env = env->next;
			}
		}
	}
}

int	new_redirection(char **str, int start, t_cmd *command)
{
	int		end;

	end = start;
	parse_rdir_type(*str, &end, command);
	if (check_redirections((*str)[end]))
		return (1);
	if (parse_files(*str, &end, command))
		return (1);
	remove_char(str, start, end);
	find_replace_tild(&(command->files[command->n_rdirs]), g_vars.env);
	remove_quotes(&(command->files[command->n_rdirs]));
	(command->n_rdirs)++;
	if (redirect_output(command, command->n_rdirs - 1)
		|| redirect_input(command, command->n_rdirs - 1))
		return (1);
	return (0);
}

int	create_redirection(char **str, t_cmd *command)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
			while ((*str)[++i] != '\'')
				;
		if ((*str)[i] == '"')
			while ((*str)[++i] != '"')
				;
		if ((*str)[i] == '<' || (*str)[i] == '>')
		{
			if (new_redirection(str, i, command))
				return (1);
			i = -1;
		}
		i++;
	}
	command->files[command->n_rdirs] = NULL;
	return (0);
}

int	redirections(char **str, t_cmd *command)
{
	int	nb_redirections;

	nb_redirections = count_redirections(*str);
	if (nb_redirections)
	{
		command->rdir_types = malloc(
				sizeof(int) * count_redirections(*str));
		if (!(command->rdir_types))
			return (error_parsing("Malloc Error\n", 2));
		command->files = malloc(
				sizeof(char *) * count_redirections(*str));
		if (!(command->files))
			return (error_parsing("Malloc Error\n", 2));
		if (create_redirection(str, command))
			return (1);
	}
	return (0);
}
