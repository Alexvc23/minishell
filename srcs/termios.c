/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:05:04 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/20 19:50:06 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 
we set attributes as needed for prompt, echoing passed input,
stablishing cannocal input and enabling sign handling
*/
void	ft_termios(void)
{
	int	result[2];

	result[0] = tcgetattr(0, &g_vars.term_save);
	result[1] = tcgetattr(0, &g_vars.term_new);
	if (result[0] || result[1])
		perror("tcsetattr\n");
	g_vars.term_new.c_lflag = (ECHO | ICANON | ISIG);
	if (tcsetattr(0, 0, &g_vars.term_new))
		perror("tcsetattr\n");
}

/* restablished default termios attributes */
void	reset_termios(void)
{
	tcsetattr(0, 0, &g_vars.term_save);
}
