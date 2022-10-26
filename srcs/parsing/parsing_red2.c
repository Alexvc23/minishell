/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_red2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:47:25 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/26 15:07:48 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_rdir_type(char *str, int *i, t_cmd *command)
{
	if (str[*i] == '<')
	{
		if (str[++(*i)] == '<')
		{
			command->rdir_types[command->n_rdirs] = LEFT_DBL_R;
			(*i)++;
		}
		else
			command->rdir_types[command->n_rdirs] = LEFT_SGL_R;
	}
	else if (str[*i] == '>')
	{
		if (str[++(*i)] == '>')
		{
			command->rdir_types[command->n_rdirs] = RIGHT_DBL_R;
			(*i)++;
		}
		else
			command->rdir_types[command->n_rdirs] = RIGHT_SGL_R;
	}
}

int	parse_files(char *str, int *i, t_cmd *command)
{
	int	start;
	int	end;

	start = start_c(str, *i);
	end = end_red(str, start);
	command->files[command->n_rdirs] = malloc(sizeof(char) * (end - start + 2));
	if (!(command->files[command->n_rdirs]))
		return (error_parsing("Malloc Error\n", 2));
	*i = 0;
	while (start + *i <= end)
	{
		command->files[command->n_rdirs][*i] = str[start + *i];
		(*i)++;
	}
	command->files[command->n_rdirs][*i] = '\0';
	*i = end;
	return (0);
}

int	check_redirections(char c)
{
	if (ft_strchr("|&;()<>", c))
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
		if (!c)
			ft_putstr_fd("newline", 2);
		else
			ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}
