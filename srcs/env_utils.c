/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:18:34 by jvalenci          #+#    #+#             */
/*   Updated: 2022/10/22 17:10:36 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_node_value(t_env **head, char *key)
{
	t_env	*tmp;

	tmp = *head;
	if (!*head)
		return (NULL);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**ft_env_to_key_array(t_env **env)
{
	char	**arr;
	t_env	*tmp;
	size_t	env_size;
	size_t	i;

	env_size = ft_env_size(*env);
	arr = malloc(sizeof(char *) * (env_size + 1));
	arr[env_size] = NULL;
	if (!env_size)
		return (arr);
	i = 0;
	tmp = *env;
	while (tmp)
	{
		arr[i++] = ft_strdup(tmp->key);
		tmp = tmp->next;
	}
	return (arr);
}

static char	*ft_env_join(char *key, char *value)
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

	envsize = ft_env_size(*env);
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

void	free_arr(void **arr)
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
