/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 20:29:42 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/05 16:58:52 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include <stdlib.h>

//redirections types
# define LEFT_SGL_R 0
# define RIGHT_SGL_R 1
# define LEFT_DBL_R 2
# define RIGHT_DBL_R 3

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*com;
	int				n_args;
	char			**args;
	int				n_rdirs;
	int				*rdir_types;
	char			**files;
	char			*in;
	char			*out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	t_cmd			*lst_com;
}				t_minishell;

#endif