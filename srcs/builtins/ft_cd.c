/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:18:34 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/22 18:16:12 by abouchet         ###   ########lyon.fr   */
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
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	else
		ft_putstr_fd(msg, STDERR_FILENO);
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
			return (ft_error("No such file or directory", path, 1));
		else if (!(sb.st_mode & S_IRUSR))
			return (ft_error("Permission denied", path, 1));
		else if (!(sb.st_mode & S_IFDIR))
			return (ft_error("Not a directory", path, 1));
	}
	return (0);
}

/* Handles how we passed  path argument to the function ft_chdir  and updates 
   t_env struct variables $PWD and $OLDPWD*/
static int	ft_go_to(t_env **env, char *path, int cd_type)
{
	char	*old_wd;
	char	*new;
	int		err_type;

	old_wd = getcwd(NULL, 0);
	new = path;
	if (!old_wd || !path)
		err_type = ft_error("No env variable found", NULL, 1);
	update_env(env, ft_strdup("OLDPWD"), ft_strdup(old_wd));
	if (cd_type == CD_HOME_AND_PATH)
		new = ft_strjoin(ft_get_node_value(env, "HOME"), path);
	else if (cd_type == CD_CURREN_AND_PATH)
		new = ft_strjoin(old_wd, path);
	if (!new)
		return (ft_error("Error joining strings", NULL, 1));
	err_type = ft_chdir(new);
	if (cd_type == CD_OLD)
		printf("%s\n", getcwd(NULL, 0));
	update_env(env, ft_strdup("PWD"), getcwd(NULL, 0));
	free(new);
	return (err_type);
}

/*
   change directory program, handling the following cases:
   1) cd || cd "~" || cd "--"  ---> replasing any of the following
   charancters "~ -- cd" by the environment variable $HOME......................
   2) cd "-" change current directory to the previous one visited, $OLDPWD. Then
   output the path to stdout....................................................
   3) cd "~/" we join the enviroment variable $HOME and the path after the 
   character ~ having at the end a absolute path................................
   4) cd + absolute path, change directory tho any absolute path passed as
   argument
 */
int	ft_cd(t_cmd *cmd, t_env **env)
{
	if (cmd->n_args > 2)
		return (ft_error("cd: too many arguments", NULL, 0));
	if (!cmd->n_args
		|| (cmd->n_args == 2 && !ft_strncmp(cmd->args[1], "~", 2))
		|| (cmd->n_args == 2 && !ft_strncmp(cmd->args[1], "--", 3)))
		return (ft_go_to(env,
				ft_strdup(ft_get_node_value(env, "HOME")), CD_HOME));
	if ((cmd->n_args == 2 && !ft_strncmp(cmd->args[1], "-", 2)))
		return (ft_go_to(env,
				ft_strdup(ft_get_node_value(env, "OLDPWD")), CD_OLD));
	if ((cmd->n_args == 2 && !ft_strncmp(cmd->args[1], "~/", 3)))
		return (ft_go_to(env, ft_strdup((cmd->args[1] + 1)), CD_HOME_AND_PATH));
	if ((cmd->n_args == 2 && !ft_strncmp(cmd->args[1], "/", 2)))
		return (ft_go_to(env, ft_strdup((cmd->args[1])), CD_ABSOLUTE));
	if ((cmd->n_args == 2 && cmd->args[1]))
		return (ft_go_to(env,
				ft_strjoin("/", cmd->args[1]), CD_CURREN_AND_PATH));
	return (0);
}
