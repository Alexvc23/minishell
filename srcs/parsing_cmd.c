/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 06:38:30 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/11 08:29:06 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_command(char **str, t_cmd *command)
{
	int	start;
	int	end;
	int	i;

	start = start_c(*str, 0);
	end = end_arg(*str, start);
	command->com = malloc(sizeof(char) * (end - start + 2));
	if (!(command->com))
		return (error_parsing("Malloc Error"));
	i = 0;
	while (start + i <= end)
	{
		command->com[i] = (*str)[start + i];
		i++;
	}
	command->com[i] = '\0';
	return (0);
}

t_cmd	*last_cmd(t_cmd *cmd)
{
	if (cmd == 0)
		return (0);
	while (cmd->next != 0)
		cmd = cmd->next;
	return (cmd);
}

int	add_back_cmd(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*last;

	if (*cmds == NULL)
		*cmds = new;
	else
	{
		last = last_cmd(*cmds);
		last->next = new;
	}
	return (0);
}

int	new_command(char *str, int start, int end)
{
	t_cmd	*new_cmd;
	char	*cmd_str;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (error_parsing("Malloc Error"));
	init_command(new_cmd);
	cmd_str = ft_substr(str, start, end - start);
	if (find_var(&cmd_str, g_vars.env))
		return (1);
	if (redirections(&cmd_str, new_cmd))
		return (1);
	if (parse_command(&cmd_str, new_cmd))
		return (1);
	remove_quotes(&(new_cmd->com));
	if (arguments(&cmd_str, new_cmd))
		return (1);
	free(cmd_str);
	add_back_cmd(&g_vars.cmd, new_cmd);
	return (0);
}

int	create_commands(char *str)
{
	int	i;
	int	j;
	int	n_com;

	i = 0;
	j = i;
	n_com = -1;
	while (str[i])
	{
		if (str[i] == '\'')
			while (str[++i] != '\'')
				;
		if (str[i] == '"')
			while (str[++i] != '"')
				;
		if (str[i] == '|')
			if (new_command(str, j, i - 1))
				return (1);
		if (str[i] == '|')
			j = i + 1;
		if (!str[++i])
			if (new_command(str, j, i))
				return (1);
	}
	return (0);
}

//(UNE COMMANDE PEUT ETRE EN MAJ)
// "" : print tout dans les "" et affiche la valeur les variables
// '' : print tout dans les '' meme les variables avec $

//$ : variable d'environnement
//$? : remplacé par le dernier output d'une commande effectuée auparavant

//(TOUJOURS NOM DE FICHIER APRES > < >> <<)
// A < B C : redirige le contenu de B dans l'entree A, puis execute AC
// A > B C : redirige la sortie de AC dans le fichier B
// A << B C : (heredoc) attend que B soit écrit, puis execute AC
// A >> B C : (append) redirige la sortie en mode append (reset pas le fichier)
// | : execute des commandes avec link des input/output des commandes