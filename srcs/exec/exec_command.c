/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:18:34 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/22 18:15:41 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exec_cmd(t_cmd *cmd, t_env **env)
{
	char	**arr_env;
	char	*path_cmd;

	if (ft_is_builtin(cmd))
		exit(exec_builtin(cmd, env));
	arr_env = ft_env_to_array(env);
	path_cmd = ft_get_cmd(ft_find_path(arr_env), cmd->com);
	execve(path_cmd, cmd->args, arr_env);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (errno != 14 || (ft_strchr(cmd->com, '/')))
		printf("%s: %s.\n", cmd->com, strerror(errno));
	else
		printf("Command '%s' not found.\n", cmd->com);
	dup2(g_vars.stdout, STDOUT_FILENO);
	free(path_cmd);
	free_arr((void **)arr_env);
	if (errno == 2 || errno == EACCES)
		exit((errno == 2) * 127 + (errno == EACCES) * 126);
	exit(1);
}
