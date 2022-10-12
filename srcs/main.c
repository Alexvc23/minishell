/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:48:31 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/12 14:27:03 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* we count the number of nodes in a linked list passing as argumet its head */
int	ft_size_list(t_env *head)
{
	int		count;
	t_env	*ptr;

	if (!head)
		return (0);
	ptr = head;
	count = 0;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

// A second one that works with cmd
int	ft_cmd_size(t_cmd *cmd)
{
	int		count;
	t_cmd	*ptr;

	if (!cmd)
		return (0);
	ptr = cmd;
	count = 0;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

static t_env	*ft_new_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

static t_env	*ft_last_node(t_env *head)
{
	t_env	*tmp;

	if (!head)
		return (0);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static void	ft_add_node_back(t_env **head, t_env *new)
{
	t_env	*ptr;

	ptr = *head;
	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	ptr = ft_last_node(*head);
	ptr->next = new;
}

void	ft_update_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	if (!env || !key || !value)
		return ;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(key) + 1))
		{
			free(tmp->value);
			free(key);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	tmp = *env;
	ft_add_node_back(&tmp, ft_new_node(key, value));
	return ;
}

int	ft_is_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->com, "echo", ft_strlen("echo") + 1))
		return (1);
	if (!ft_strncmp(cmd->com, "export", ft_strlen("export") + 1))
		return (1);
	if (!ft_strncmp(cmd->com, "unset", ft_strlen("unset") + 1))
		return (1);
	if (!ft_strncmp(cmd->com, "env", ft_strlen("env") + 1))
		return (1);
	if (!ft_strncmp(cmd->com, "pwd", ft_strlen("pwd") + 1))
		return (1);
	if (!ft_strncmp(cmd->com, "cd", ft_strlen("cd") + 1))
		return (1);
	if (!ft_strncmp(cmd->com, "exit", ft_strlen("exit") + 1))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_env **env)
{
	if (!ft_strncmp(cmd->com, "exit", ft_strlen("exit") + 1))
		return (ft_exit(cmd));
	else if (!ft_strncmp(cmd->com, "echo", ft_strlen("echo") + 1))
		return (ft_echo(cmd));
	else if (!ft_strncmp(cmd->com, "export", ft_strlen("export") + 1))
		return (ft_export(cmd, env));
	else if (!ft_strncmp(cmd->com, "unset", ft_strlen("unset") + 1))
		return (ft_unset(cmd, env));
	else if (!ft_strncmp(cmd->com, "env", ft_strlen("env") + 1))
		return (ft_env(cmd, env));
	else if (!ft_strncmp(cmd->com, "pwd", ft_strlen("pwd") + 1))
		return (ft_pwd(cmd, env));
	else if (!ft_strncmp(cmd->com, "cd", ft_strlen("cd") + 1))
		return (ft_cd(cmd, env));
	return (1);
}

char	*ft_env_join(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

char	**ft_env_to_array(t_env **env)
{
	char	**arr;
	t_env	*tmp;
	int		envsize;
	int		i;

	envsize = ft_size_list(*env);
	arr = malloc(sizeof(char *) * (envsize + 1));
	arr[envsize] = NULL;
	if (!envsize)
		return (arr);
	i = 0;
	tmp = *env;
	while (tmp)
	{
		arr[i++] = ft_env_join(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (arr);
}

char	*ft_find_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			return (env[i] + 5);
	}
	return (NULL);
}

char	*ft_get_cmd(char *v_path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*new_cmd;
	char	**path;

	i = -1;
	if (!cmd || !cmd[0])
		exit(0);
	if (!v_path || (ft_strchr(cmd, '/') && !access(cmd, 0)))
		return (cmd);
	path = ft_split(v_path, ':');
	while (path && path[++i])
	{
		tmp = ft_strjoin("/", cmd);
		new_cmd = ft_strjoin(path[i], tmp);
		if (!access(new_cmd, 0))
		{
			free(tmp);
			return (new_cmd);
		}
		free(tmp);
		free(new_cmd);
	}
	return (cmd);
}

void	ft_free(void **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	exec_cmd(t_cmd *cmd, t_env **env)
{
	char	**arr_env;
	char	*path_cmd;

	if (ft_is_builtin(cmd))
		exit(exec_builtin(cmd, env));
	arr_env = ft_env_to_array(env);
	path_cmd = ft_get_cmd(ft_find_path(arr_env), cmd->com);
	execve(path_cmd, cmd->args, arr_env); //s'arrete ici si réussi
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (errno != 14 || (ft_strchr(cmd->com, '/')))
		printf("%s: %s.\n", cmd->com, strerror(errno));
	else
		printf("Command '%s' not found.\n", cmd->com);
	dup2(g_vars.stdout, STDOUT_FILENO);
	free(path_cmd);
	ft_free((void **)arr_env);
	if (errno == 2 || errno == EACCES)
		exit((errno == 2) * 127 + (errno == EACCES) * 126);
	exit(1);
}

void	dup_redirec(t_cmd *cmd)
{
	int	in;
	int	out;

	if (cmd->in)//&& !cmd->heredoc
	{
		in = open(cmd->in, O_RDONLY, 0777);
		if (in < 0)
			exit(1);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (cmd->out)
	{
		out = open(cmd->out, O_WRONLY | O_CREAT | (
					O_TRUNC) | (
					O_APPEND), 0777);
					//O_TRUNC * (cmd->append != 2)) | (
					//O_APPEND * (cmd->append == 2)), 0777);
		if (out < 0)
			exit(1);
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

pid_t	exec_single(t_cmd *cmd, t_env **env, int id)
{
	pid_t	pid;

	if (id == 0 && ft_is_builtin(cmd))
	{
		dup_redirec(cmd);
		g_vars.status = exec_builtin(cmd, env);
		dup2(g_vars.stdin, STDIN_FILENO);
		dup2(g_vars.stderr, STDERR_FILENO);
		dup2(g_vars.stdout, STDOUT_FILENO);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid)
		return (pid);
	dup_redirec(cmd);
	exec_cmd(cmd, env);
	return (pid);
}

pid_t	exec_heredoc(t_cmd *cmd)
{
	pid_t	pid;
	int		file[2];

	if (pipe(file) < 0)
		return (-1);
	pid = fork();
	if (pid)
	{
		dup2(file[0], STDIN_FILENO);
		close(file[0]);
		close(file[1]);
	}
	else
	{
		if (!cmd->in)
			cmd->in = ft_strdup("");
		pid = write(file[1], cmd->in, ft_strlen(cmd->in));
		close(file[0]);
		close(file[1]);
		exit(pid);
	}
	return (pid);
}

pid_t	exec_pipe(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	int		files[2];

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
	}
	else
	{
		dup2(files[1], STDOUT_FILENO);
		close(files[0]);
		close(files[1]);
		dup_redirec(cmd);
		exec_cmd(cmd, env);
	}
	return (pid);
}

pid_t	exec_type(t_cmd *cmd, t_env **env, int id)
{
	int	pid;

	//if (cmd->heredoc)
	//	pid = exec_heredoc(cmd);
	if (!cmd->next)
	{
		dup2(g_vars.stdout, STDOUT_FILENO);
		pid = exec_single(cmd, env, id);
		dup2(g_vars.stdin, STDIN_FILENO);
	}
	else
		pid = exec_pipe(cmd, env);
	return (pid);
}

void	exec_wait(t_cmd *cmd)
{
	int				status;
	unsigned int	i;

	if (g_vars.n_cmd > 1 || (cmd && !ft_is_builtin(cmd)))
	{
		i = -1;
		while (++i < (unsigned int)g_vars.n_cmd)
			waitpid(g_vars.pids[i], &status, 0);
		if (WIFEXITED(status))
			g_vars.status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			printf("%d\n", WTERMSIG(status));
			g_vars.status = 128 + WTERMSIG(status);
		}
	}
	g_vars.n_cmd = 0;
	free(g_vars.pids);
}

void	exec(void)
{
	int		i;
	t_cmd	*cmd;

	cmd = g_vars.cmd;
	g_vars.pids = calloc(g_vars.n_cmd, sizeof(int));
	if (!g_vars.n_cmd || !g_vars.pids)
		return ;
	i = 0;
	while (i < g_vars.n_cmd)
	{
		g_vars.pids[i] = exec_type(cmd, &g_vars.env, i);
		if (cmd->next)
			cmd = cmd->next;
		i++;
	}
	ft_update_env(&g_vars.env, ft_strdup("_"),
		ft_strdup(g_vars.cmd->args[g_vars.cmd->n_args - 1]));
	exec_wait(g_vars.cmd);
	dup2(g_vars.stdin, STDIN_FILENO);
	dup2(g_vars.stdout, STDOUT_FILENO);
	dup2(g_vars.stderr, STDERR_FILENO);
}

////////////////////////////////SIGNALS + MAIN//////////////////////////////////

void	handler_shell(int status)
{
	if (status == SIGINT)
	{
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "\n", 1);
	}
//	else if (status == SIGQUIT)
//	{
//		write(1, "\n", 1);
//		rl_replace_line("", 0);
//	}
	rl_on_new_line();
	rl_redisplay();
}

int	ft_prompt(void)
{
	char	*str;

	rl_on_new_line();
	str = readline(BOLD PINK "Minishell_> " END);
	if (!str)
		ft_exit(NULL);

	g_vars.n_cmd = ft_cmd_size(g_vars.cmd);
	if (create_commands(str) == 0)
		exec();
	print_com(g_vars.cmd);
	free_commands(&g_vars.cmd);
	add_history(str);
	if (str)
		free(str);
	return (0);
}

void	ft_increase_shlvl(t_env	*env)
{
	while (env->next
		&& ft_strncmp(env->key, "SHLVL", ft_strlen("SHLVL") + 1))
		env = env->next;
	if (!ft_strncmp(env->key, "SHLVL", ft_strlen("SHLVL") + 1))
		env->value = ft_itoa(ft_atoi(env->value) + 1);
}

void	init_shell(char **envp)
{
	g_vars.stdin = dup(STDIN_FILENO);
	g_vars.stdout = dup(STDOUT_FILENO);
	g_vars.stderr = dup(STDERR_FILENO);
	create_envs(envp, &g_vars.env);
	ft_increase_shlvl(g_vars.env);
	g_vars.cmd = NULL;
}
//print_env(g_vars.env);

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		return (error_parsing("Error Minishell called with too much argv"));
	signal(SIGINT, handler_shell);
	signal(SIGQUIT, handler_shell);
	init_shell(envp);
	while (1)
		if (ft_prompt())
			return (1);
	rl_clear_history();
	free_envs(&g_vars.env);
	return (g_vars.status);
}

//COMMANDES A TESTER
//cat minishell.h | grep include > outfile | wc -l
//