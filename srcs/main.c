/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:48:31 by abouchet          #+#    #+#             */
/*   Updated: 2022/10/25 18:34:44 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_prompt(void)
{
	char	*str;

	rl_on_new_line();
	ft_termios();
	signal(SIGINT, handler_shell);
	signal(SIGQUIT, handler_shell);
	str = readline(BOLD PINK "Minishell_> " END);
	if (!str)
	{
		ft_putstr_fd("exit\n", 1);
		exit(g_vars.status);
	}
	reset_termios();
	if (create_commands(str) == 0)
	{
		exec();
	}
	free_commands(&g_vars.cmd);
	add_history(str);
	if (str)
		free(str);
	return (0);
}
//print_com(g_vars.cmd);

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
	g_vars.h_pid = 0;
	g_vars.cmd = NULL;
}
//print_env(g_vars.env);

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		return (error_parsing("Error Minishell called with too much argv\n", 2));
	init_shell(envp);
	while (1)
		if (ft_prompt())
			return (1);
	rl_clear_history();
	free_envs(&g_vars.env);
	return (g_vars.status);
}
