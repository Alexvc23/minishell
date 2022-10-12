/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:35:17 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/09 06:35:20 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_redirections(int *rdir_types, char **files, int n)
{
	int	i;

	printf("	%d Redirections : \n", n);
	i = 0;
	while (i < n)
	{
		if (rdir_types[i] == LEFT_SGL_R)
			printf("		< ");
		else if (rdir_types[i] == RIGHT_SGL_R)
			printf("		> ");
		else if (rdir_types[i] == LEFT_DBL_R)
			printf("		<< ");
		else if (rdir_types[i] == RIGHT_DBL_R)
			printf("		>> ");
		printf("|%s|\n", files[i]);
		i++;
	}
}

void	print_arguments(char **args, int n)
{
	int	i;

	printf("	%d Arguments : \n", n);
	i = 0;
	while (i < n)
	{
		printf("		|%s|\n", args[i]);
		i++;
	}
}

void	print_com(t_cmd *commands)
{
	int	i;

	i = 0;
	while (commands)
	{
		printf("COMMANDE Nº%d :\n		|%s|\n", i + 1, commands->com);
		print_arguments(commands->args, commands->n_args);
		print_redirections(commands->rdir_types,
			commands->files, commands->n_rdirs);
		printf("\n");
		commands = commands->next;
		i++;
	}
}

void	print_env(t_env *envs)
{
	int	i;

	i = 0;
	while (envs)
	{
		printf("VARIABLE D'ENVIRONNEMENT Nº%d :\n", i + 1);
		printf ("key :		%s\n", envs->key);
		printf ("value :		%s\n", envs->value);
		envs = envs->next;
		i++;
	}
}
