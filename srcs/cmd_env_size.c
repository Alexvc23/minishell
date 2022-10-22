/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:04:02 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/22 16:52:18 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* we count the number of nodes in a linked list passing as argumet its env */
int	ft_env_size(t_env *env)
{
	int		count;
	t_env	*ptr;

	if (!env)
		return (0);
	ptr = env;
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
