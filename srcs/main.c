/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:48:31 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/06 14:40:32 by abouchet         ###   ########lyon.fr   */
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

int	whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

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

int	count_arguments(char *str)
{
	int	i;
	int	nb_arguments;

	i = 0;
	while (whitespace(str[i]))
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
		if (whitespace(str[i]) || !str[i])
			nb_arguments++;
		while (whitespace(str[i]))
			i++;
	}
	return (nb_arguments);
}

int	start_c(char *str, int i)
{
	int	start;

	start = i;
	while (str[start] && whitespace(str[start]))
		start++;
	return (start);
}

int	end_red(char *str, int start)
{
	int	end;

	end = start;
	while (str[end] && !whitespace(str[end])
		&& str[end] != '>' && str[end] != '<')
	{
		if (str[end] == '\'')
			while (str[++end] && str[end] != '\'')
				;
		if (str[end] == '"')
			while (str[++end] && str[end] != '"')
				;
		end++;
	}
	return (end - 1);
}

int	end_arg(char *str, int start)
{
	int	end;

	end = start;
	while (str[end] && !whitespace(str[end]))
	{
		if (str[end] == '\'')
			while (str[++end] && str[end] != '\'')
				;
		if (str[end] == '"')
			while (str[++end] && str[end] != '"')
				;
		end++;
	}
	return (end - 1);
}

int	parse_rdir_type(char *str, int *i, t_cmd *command)
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
	return (0);
}

int parse_files(char *str, int *i, t_cmd *command)
{
	int	start;
	int	end;

	start = start_c(str, *i);
	end = end_red(str, start);
	command->files[command->n_rdirs] = malloc(sizeof(char) * (end - start + 2));
	if (!(command->files[command->n_rdirs]))
		return (1);
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

int	remove_char(char **str, int start, int end)
{
	char	*str1;
	char	*str2;

	str1 = ft_substr(*str, 0, start);
	str2 = ft_substr(*str, end + 1,
			ft_strlen(*str) - (end + 1));
	free(*str);
	*str = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (0);
}

int	add_char(char **str, int i, char *add)
{
	char	*str1;
	char	*str2;

	str1 = ft_substr(*str, 0, i);
	str2 = ft_substr(*str, i,
			ft_strlen(*str) - i);
	free(*str);
	*str = ft_strjoin(str1, ft_strjoin(add, str2));
	free(str1);
	free(str2);
	return (0);
}

int	replace_var(char **str, int start, int end, t_env *env)
{
	char	*var;

	var = ft_substr(*str, start + 1, end - start);
	if (remove_char(str, start, end))
		return (1);
	while (env)
	{
		if (!ft_strncmp(var, env->key, ft_strlen(var) + 1))
			if (add_char(str, start, env->value))
				return (1);
		env = env->next;
	}
	free(var);
	return (0);
}

int	find_var(char **str, t_env *env)
{
	int	i;
	int	start;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
			while ((*str)[++i] != '\'')
				;
		if ((*str)[i] == '$')
		{
			start = i;
			i++;
			while ((*str)[i] && (*str)[i] != '"' && (*str)[i] != '\''
					&& (*str)[i] != '$' && !whitespace((*str)[i]))
				i++;
			if (replace_var(str, start, i - 1, env))
				return (1);
			i = start;
		}
		i++;
	}
	return (0);
}

int	remove_quotes(char	**str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			remove_char(str, i, i);
			while ((*str)[i] != '\'')
				i++;
			remove_char(str, i, i);
		}
		if ((*str)[i] == '"')
		{
			remove_char(str, i, i);
			while ((*str)[i] != '"')
				i++;
			remove_char(str, i, i);
		}
		i++;
	}
	return (0);
}

int	new_redirection(char **str, int start, t_cmd *command)
{
	int		end;

	end = start;
	if (parse_rdir_type(*str, &end, command))
		return (1);
	if (parse_files(*str, &end, command))
		return (1);
	if (remove_char(str, start, end))
		return (1);
	if (remove_quotes(&(command->files[command->n_rdirs])))
		return (1);
	(command->n_rdirs)++;
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
			return (1);
		command->files = malloc(
				sizeof(char *) * count_redirections(*str));
		if (!(command->files))
			return (1);
		if (create_redirection(str, command))
			return (1);
	}
	return (0);
}

int parse_args(char *str, int *i, t_cmd *command)
{
	int	start;
	int	end;

	start = start_c(str, *i);
	end = end_arg(str, start);
	command->args[command->n_args] = malloc(sizeof(char) * (end - start + 2));
	if (!(command->args[command->n_args]))
		return (1);
	*i = 0;
	while (start + *i <= end)
	{
		command->args[command->n_args][*i] = str[start + *i];
		(*i)++;
	}
	command->args[command->n_args][*i] = '\0';
	*i = end;
	return (0);
}

int new_argument(char **str, int start, t_cmd *command)
{
	int	end;

	end = start;
	if (parse_args(*str, &end, command))
		return (1);
	if (remove_char(str, start, end))
		return (1);
	if (remove_quotes(&(command->args[command->n_args])))
		return (1);
	(command->n_args)++;
	return (0);
}

int	create_argument(char **str, t_cmd *command)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if (!whitespace((*str)[i]))
		{
			if (new_argument(str, i, command))
				return (1);
			i = -1;
		}
		i++;
	}
	return (0);
}

int	arguments(char **str, t_cmd *command)
{
	int	nb_arguments;

	nb_arguments = count_arguments(*str);
	if (nb_arguments)
	{
		command->args = malloc(
				sizeof(char *) * count_arguments(*str));
		if (!(command->args))
			return (1);
		if (create_argument(str, command))
			return (1);
	}
	return (0);
}

int	init_command(t_cmd *new_cmd)
{
	new_cmd->com = NULL;
	new_cmd->n_args = 0;
	new_cmd->args = NULL;
	new_cmd->n_rdirs = 0;
	new_cmd->rdir_types = NULL;
	new_cmd->files = NULL;
	new_cmd->in = NULL;
	new_cmd->out = NULL;
	new_cmd->next = NULL;
	return (0);
}

int	parse_command(char **str, t_cmd *command)
{
	int	start;
	int	end;
	int	i;

	start = start_c(*str, 0);
	end = end_arg(*str, start);
	command->com = malloc(sizeof(char) * (end - start + 2));
	if (!(command->com))
		return (1);
	i = 0;
	while (start + i <= end)
	{
		command->com[i] = ft_tolower((*str)[start + i]);
		i++;
	}
	command->com[i] = '\0';
	if (remove_char(str, start, end))
		return (1);
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

int	new_command(char *str, int start, int end, t_cmd **commands, t_env *env)
{
	t_cmd	*new_cmd;
	char	*cmd_str;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (0);
	if (init_command(new_cmd))
		return (1);
	cmd_str = ft_substr(str, start, end - start);
	if (find_var(&cmd_str, env))
		return (1);
	if (redirections(&cmd_str, new_cmd))
		return (1);
	if (parse_command(&cmd_str, new_cmd))
		return (1);
	if (remove_quotes(&(new_cmd->com)))
		return (1);
	if (arguments(&cmd_str, new_cmd))
		return (1);
	free(cmd_str);
	add_back_cmd(commands, new_cmd);
	return (0);
}

int	create_commands(char *str, t_cmd **commands, t_env *env)
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
			if (new_command(str, j, i - 1, commands, env))
				return (1);
		if (str[i] == '|')
			j = i + 1;
		if (!str[++i])
			if (new_command(str, j, i, commands, env))
				return (1);
	}
	return (0);
}

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

t_env	*last_env(t_env *env)
{
	if (env == 0)
		return (0);
	while (env->next != 0)
		env = env->next;
	return (env);
}

int	add_back_env(t_env **envs, t_env *new)
{
	t_env	*last;

	if (*envs == NULL)
		*envs = new;
	else
	{
		last = last_env(*envs);
		last->next = new;
	}
	return (0);
}

int	new_env(char *str, t_env **envs)
{
	int		equal;
	t_env	*new_elem;

	new_elem = malloc(sizeof(t_env));
	if (!new_elem)
		return (0);
	equal = 0;
	while (str[equal] && str[equal] != '=')
		equal++;
	new_elem->key = ft_substr(str, 0, equal);
	new_elem->value = ft_substr(str, equal + 1, ft_strlen(str) - (equal + 1));
	new_elem->next = NULL;
	add_back_env(envs, new_elem);
	return (0);
}

int	create_envs(char **envp, t_env **envs)
{
	int	i;

	*envs = NULL;
	i = 0;
	while (envp[i])
	{
		if (new_env(envp[i], envs))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_cmd	*commands;
	t_env	*envs;

	(void)argc;
	(void)argv;
	(void)envp;
	create_envs(envp, &envs);
	//print_env(envs);
	str = readline("% ");
	commands = NULL;
	create_commands(str, &commands, envs);
	print_com(commands);
	free_commands(&commands);
	free_envs(&envs);
	free(str);
	return (0);
}

//if then elif else fi time for in until while do done
// case esac coproc select function { } [[ ]] !
// : reconnais ces mots quand il y a pas de guillemets

//(UNE COMMANDE PEUT ETRE EN MAJ)
//(UNE COMMANDE PEUT ETRE ENTRE GUILLEMETS UNE SEULE FOIS)
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

//COMMANDES A TESTER
//cat minishell.h | grep include > outfile | wc -l
//