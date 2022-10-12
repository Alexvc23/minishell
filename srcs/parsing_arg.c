/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:42:21 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/12 13:46:28 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_arguments(char *str)
{
	int	i;
	int	nb_arguments;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	nb_arguments = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == '"')
			while (str[++i] && str[i] != '"')
				;
		i++;
		if (is_whitespace(str[i]) || !str[i])
			nb_arguments++;
		while (is_whitespace(str[i]))
			i++;
	}
	return (nb_arguments);
}

int	parse_args(char *str, int start, int end, t_cmd *command)
{
	int	i;

	command->args[command->n_args] = malloc(sizeof(char) * (end - start + 2));
	if (!(command->args[command->n_args]))
		return (error_parsing("Malloc Error"));
	i = 0;
	while (start + i <= end)
	{
		command->args[command->n_args][i] = str[start + i];
		i++;
	}
	command->args[command->n_args][i] = '\0';
	return (0);
}

int	new_argument(char **str, int i, t_cmd *command)
{
	int	start;
	int	end;

	start = start_c(*str, i);
	if ((*str)[start] == '\0')
		remove_char(str, i, start);
	else
	{
		end = end_arg(*str, start);
		if (parse_args(*str, start, end, command))
			return (1);
		remove_char(str, i, end);
		remove_quotes(&(command->args[command->n_args]));
		(command->n_args)++;
	}
	return (0);
}

int	create_argument(char **str, t_cmd *command)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if (new_argument(str, i, command))
			return (1);
	}
	command->args[command->n_args] = NULL;
	return (0);
}

int	arguments(char **str, t_cmd *command)
{
	int	nb_arguments;

	nb_arguments = count_arguments(*str);
	if (nb_arguments)
	{
		command->args = malloc(
				sizeof(char *) * (count_arguments(*str) + 1));
		if (!(command->args))
			return (error_parsing("Malloc Error"));
		if (create_argument(str, command))
			return (1);
	}
	return (0);
}
