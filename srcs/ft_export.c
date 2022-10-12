/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:58:13 by fdevigne          #+#    #+#             */
/*   Updated: 2022/10/11 08:54:55 by abouchet         ###   ########lyon.fr   */
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

static char	*ft_get_node_value(t_env **head, char *key)
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

static size_t	ft_env_size(t_env **env)
{
	t_env	*tmp;
	size_t	size;

	if (!env || !*env)
		return (0);
	size = 0;
	tmp = *env;
	while (tmp && ++size)
		tmp = tmp->next;
	return (size);
}

static char	**ft_env_to_key_array(t_env **env)
{
	char	**arr;
	t_env	*tmp;
	size_t	env_size;
	size_t	i;

	env_size = ft_env_size(env);
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

static int	ft_is_valid_key(char *key)
{
	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (*(++key))
	{
		if (!ft_isalpha(*key) && !ft_isdigit(*key) && *key != '_')
		{
			if (*key == '=')
				return (1);
			return (0);
		}
	}
	return (1);
}

static void	ft_update_env(t_env **env, char *key, char *value)
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

static int	ft_putenv(t_env **env, char **keys)
{
	char	*value;
	int		i;

	i = -1;
	while (keys[++i])
	{
		value = ft_strdup(ft_get_node_value(env, keys[i]));
		printf("declare -x %s=\"%s\"\n", keys[i], value);
		free(value);
	}
	//ft_free((void **) keys);
	return (0);
}

/* 
--> Fetch all env keys and puts in a array
--> Sorts the array alphabetically
--> pass the array to ft_putenv and return success code 0 
*/
static int	ft_sort_env_arr(t_env **env)
{
	char	**keys;
	char	*tmp;
	int		len;
	int		i;
	int		j;

	keys = ft_env_to_key_array(env);
	len = 0;
	while (keys[len])
		len++;
	i = -1;
	while (++i < len - 1)
	{
		j = -1;
		while (++j + i < len)
		{
			if (ft_strncmp(keys[i], keys[i + j], -1) > 0)
			{
				tmp = keys[i];
				keys[i] = keys[i + j];
				keys[i + j] = tmp;
			}
		}
	}
	return (ft_putenv(env, keys));
}

static int	ft_export_err(char *err)
{
	ft_putstr_fd("Invalid key name: '", STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("'.\n", STDERR_FILENO);
	return (1);
}

static int	ft_export_one(char *str, t_env **env)
{
	char	*key;
	char	*val;
	int		err;
	int		i;

	key = str;
	err = 0;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!ft_is_valid_key(key))
		return (ft_export_err(key));
	if (!str[i])
		return (1);
	str[i] = '\0';
	val = &str[i + 1];
	if (ft_is_valid_key(key))
		ft_update_env(env, ft_strdup(key), ft_strdup(val));
	str[i] = '=';
	return (err);
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	int	status;
	int	i;

	if (cmd->n_args == 1)
		return (ft_sort_env_arr(env));
	status = 0;
	i = 1;
	while (cmd->args[i])
	{
		status += ft_export_one(cmd->args[i], env);
		i++;
	}
	return (status != 0);
}
