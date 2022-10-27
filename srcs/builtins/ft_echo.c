/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:18:29 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/28 00:00:27 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* echo function with -n argument will skip \n at the end of line 
   addtionally, we handle error checking by allowing the argument -n
   as follow: "-nnnnnnnn" or "-nnnnn" -n -n -n -n -n -n.., this behavior
   should be accepted as an unique -n and skip \n at the end of argv. we
   won't accept the option -n if it is followed by anything different from 'n'
example: "-nnnnp" "-nnnnz" "-nnn " this will be printed as normal output */

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	option_n;

	option_n = 0;
	if (cmd->n_args >= 2 && ft_strncmp(cmd->args[1], "-n", 2) == 0)
		option_n = 1;
	i = 1;
	while (cmd->args[1][++i])
	{
		if (cmd->args[1][i] != 'n')
			option_n = 0;
	}
	i = 1;
	if (option_n)
		i = 2;
	while (i < cmd->n_args)
	{
		printf("%s", cmd->args[i]);
		if (i + 1 < cmd->n_args)
			printf(" ");
		i++;
	}
	if (!option_n)
		printf("\n");
	return (0);
}
