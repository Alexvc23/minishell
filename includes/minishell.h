/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 20:29:42 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/24 15:36:53 by abouchet         ###   ########lyon.fr   */
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

# include <termios.h>

//colors
# define RESET	"\033[0;0m"
# define ERASE	"\033[2K\r"
# define GREY	"\033[30m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define PINK	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"
# define BOLD	"\033[1m"
# define UNDER	"\033[4m"
# define SUR	"\033[7m"
# define END	"\033[0m"
# define CENTER	"\033[60G"

//redirections types
# define LEFT_SGL_R 0
# define RIGHT_SGL_R 1
# define LEFT_DBL_R 2
# define RIGHT_DBL_R 3

//builtin cd command
# define CD_ABSOLUTE 1
# define CD_OLD 2
# define CD_HOME_AND_PATH 3
# define CD_HOME 4 
# define CD_CURREN_AND_PATH 5

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*com;
	char			**args;
	int				n_args;
	int				*rdir_types;
	char			**files;
	int				n_rdirs;
	char			*in;
	char			*out;
	int				heredoc;
	int				append;
	struct s_cmd	*next;
}	t_cmd;

	//*com;			->	commande string
	//**args;		->	arguments string list
	//n_args;		->	nombre de d'arguments
	//n_rdirs;		->	nombre de redirections
	//*rdir_types;	->	redirections types list
	//**files;		->	redirections string list
	//*in;			->	string in
	//*out;			->	string out

typedef struct s_shell {
	int				stdin;
	int				stdout;
	int				stderr;
	int				status;
	t_env			*env;
	t_cmd			*cmd;
	int				n_cmd;
	int				*pids;
	pid_t			h_pid;
	struct termios	term_save;
	struct termios	term_new;
}	t_shell;

	//stdin		->	
	//stdout	->	
	//stderr	->	
	//status	->	status d'erreur de l'ancienne commande
	//*env		->	variables d'environnement
	//*cmd		->	commandes
	//n_cmd		->	nombre de commandes
	//*pids		->	pid des processus (enfants/parent)

t_shell	g_vars;

////////////////////////////////////////////////
////////////////////PARSING/////////////////////
////////////////////////////////////////////////

//INIT
void	init_command(t_cmd *new_cmd);

//ENVIRONNEMENTS VAR
t_env	*last_env(t_env *env);
void	add_back_env(t_env **envs, t_env *new);
int		new_env(char *str, t_env **envs);
int		create_envs(char **envp, t_env **envs);

//COMMANDES
int		parse_command(char **str, t_cmd *command);
t_cmd	*last_cmd(t_cmd *cmd);
int		add_back_cmd(t_cmd **cmds, t_cmd *new);
int		new_command(char *str, int start, int end);
int		create_commands(char *str);

//REDIRECTIONS
int		count_redirections(char *str);
int		new_redirection(char **str, int start, t_cmd *command);
int		create_redirection(char **str, t_cmd *command);
int		redirections(char **str, t_cmd *command);

void	parse_rdir_type(char *str, int *i, t_cmd *command);
int		parse_files(char *str, int *i, t_cmd *command);
int		check_redirections(char c);
int		redirect_output(t_cmd *cmd, int i);
int		redirect_input(t_cmd *cmd, int i);

//ARGUMENTS
int		count_arguments(char *str);
int		parse_args(char *str, int start, int end, t_cmd *command);
int		new_argument(char **str, int start, t_cmd *command);
int		create_argument(char **str, t_cmd *command);
int		arguments(char **str, t_cmd *command);

//VARIABLES
void	replace_var(char **str, int start, int end, t_env *env);
int		check_var(char **str, int *i, t_env *env);
int		find_var(char **str, t_env *env);

void	replace_tild(char **str, int start, t_env *env);
int		find_tild(char **str, t_env *env);

//QUOTES
void	remove_quotes(char	**str);

//UTILS
int		is_whitespace(char c);
int		start_c(char *str, int i);
int		end_red(char *str, int start);
int		end_arg(char *str, int start);

void	remove_char(char **str, int start, int end);
void	add_char(char **str, int i, char *add);

//PRINT
void	print_redirections(int *rdir_types, char **files, int n);
void	print_arguments(char **args, int n);
void	print_com(t_cmd *commands);
void	print_env(t_env *envs);

//FREE
void	free_tab(char **tab, int n);
void	free_commands(t_cmd **commands);
void	free_envs(t_env **envs);
int		error_parsing(char *err_str, int fd);

//HEREDOC
int		wait_heredoc(t_cmd *stru);

////////////////////////////////////////////////
/////////////////////EXEC///////////////////////
////////////////////////////////////////////////

//env utils
void	update_env(t_env **env, char *key, char *value);

char	*ft_get_node_value(t_env **head, char *key);
char	**ft_env_to_key_array(t_env **env);
char	**ft_env_to_array(t_env **env);
void	free_arr(void **arr);

int		ft_env_size(t_env *head);
int		ft_cmd_size(t_cmd *cmd);

//EXEC utils
void	dup_redirec(t_cmd *cmd);

//EXEC BUILTIN
int		ft_is_builtin(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, t_env **env);

//EXEC COMMAND
char	*ft_find_path(char **env);
char	*ft_get_cmd(char *v_path, char *cmd);
void	exec_cmd(t_cmd *cmd, t_env **env);

//EXEC TYPE
pid_t	exec_single(t_cmd *cmd, t_env **env, int id);
pid_t	exec_heredoc(t_cmd *cmd);
pid_t	exec_pipe(t_cmd *cmd, t_env **env);
pid_t	exec_type(t_cmd *cmd, t_env **env, int id);

//EXEC
void	exec_wait(t_cmd *cmd);
void	exec(void);

////////////////////////////////////////////////
////////////////////BUILTINS////////////////////
////////////////////////////////////////////////

int		ft_exit(t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_export(t_cmd *cmd, t_env **env);
int		ft_unset(t_cmd *cmd, t_env **env);
int		ft_env(t_cmd *cmd, t_env **env);
int		ft_pwd(t_cmd *cmd, t_env **env);
int		ft_cd(t_cmd *cmd, t_env **env);

////////////////////////////////////////////////
////////////////////SIGNALS/////////////////////
////////////////////////////////////////////////

void	handler_heredoc(int sig);
void	handler_shell(int sig);

////////////////////////////////////////////////
////////////////////TERMIOS/////////////////////
////////////////////////////////////////////////

void	ft_termios(void);
void	reset_termios(void);

////////////////////////////////////////////////
////////////////////PROMPT//////////////////////
////////////////////////////////////////////////

int		ft_prompt(void);
void	ft_increase_shlvl(t_env	*env);
void	init_shell(char **envp);
int		main(int argc, char **argv, char **envp);

#endif