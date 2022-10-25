/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:18:34 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/25 17:33:04 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Allows to print error messages to stderr, customizing it's behavior
   whether printing a cmd error or a specific message: returns the specified 
   error type*/

static int	ft_error(char *msg, char *cmd, int error_type)
{
	if (cmd)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	return (error_type);
}

/* Changes directory taking as parameter any absolute path,
   checkes if there are permissions to get in the folder and 
   checks if it is a folder and not any other type of file
   return 0 in success and 1 in error  */

static int	ft_chdir(char *path)
{
	struct stat	sb;

	if (chdir(path) < 0)
	{
		if (stat(path, &sb) < 0)
			return (ft_error(": No such file or directory", path, 1));
		else if (!(sb.st_mode & S_IRUSR))
			return (ft_error(": Permission denied", path, 1));
		else if (!(sb.st_mode & S_IFDIR))
			return (ft_error(": Not a directory", path, 1));
	}
	return (0);
}

/* Handles how we passed  path argument to the function ft_chdir  and updates 
   t_env struct variables $PWD and $OLDPWD*/

static int	ft_go_to(t_env **env, char *path, int cd_type)
{
	int		err_type;
	char	*oldpwd;

	oldpwd = ft_strdup(ft_get_node_value(env, "PWD"));
	if (cd_type == CD_HOME)
	{
		if (!path)
			return (ft_error(" not set", "HOME", 1));
	}
	else if (cd_type == CD_OLD)
	{
		if (!path)
			return (ft_error(" not set", "OLDPWD", 1));
	}
	update_env(env, ft_strdup("OLDPWD"), oldpwd);
	err_type = ft_chdir(path);
	update_env(env, ft_strdup("PWD"), getcwd(NULL, 0));
	if (cd_type == CD_OLD && !err_type)
		printf("%s\n", getcwd(NULL, 0));
	return (err_type);
}

/*static char	*relative_path(char *cmd_arg, t_env **env)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(ft_get_node_value(env, "PWD"), "/");
	path = ft_strjoin(temp, cmd_arg);
	free(temp);
	return (path);
}*/

int	ft_cd(t_cmd *cmd, t_env **env)
{
	char	*path;
	int		cd_type;
	int		err_type;

	cd_type = CD_STD;
	if (cmd->n_args == 1
		|| (cmd->n_args >= 2 && !ft_strncmp(cmd->args[1], "~", 2))
		|| (cmd->n_args >= 2 && !ft_strncmp(cmd->args[1], "--", 3)))
	{
		path = ft_strdup(ft_get_node_value(env, "HOME"));
		cd_type = CD_HOME;
	}
	else if (cmd->n_args >= 2 && !ft_strncmp(cmd->args[1], "-", 2))
	{
		path = ft_strdup(ft_get_node_value(env, "OLDPWD"));
		cd_type = CD_OLD;
	}
	else if (cmd->n_args >= 2 && !ft_strncmp(cmd->args[1], "/", 1))
		path = ft_strdup(cmd->args[1]);
	else
		path = ft_strdup(cmd->args[1]);
	err_type = ft_go_to(env, path, cd_type);
	free(path);
	return (err_type);
}
