/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:04:02 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/22 16:41:24 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	update_env(t_env **env, char *key, char *value)
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
