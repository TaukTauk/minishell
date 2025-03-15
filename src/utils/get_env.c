/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:24:20 by talin             #+#    #+#             */
/*   Updated: 2025/03/15 22:30:09 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_envi(char **env, int i)
{
	int	y;

	y = 0;
	while (y <= i)
	{
		if (env[y])
			free(env[y]);
		y++;
	}
	if (env)
		free(env);
}


void	gen_env(t_data *data)
{
	t_envp	*tmp;
	size_t	i;

	if (data->env != NULL)
		free_environ(data->env);
	i = 0;
	data->env = malloc(sizeof(*data->env) * (data->env_len + 1));
	if (!data->env)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	tmp = data->envp;
	while (tmp)
	{
		data->env[i] = ft_multjoin((char *[]){tmp->key, "=", tmp->value,
			NULL});
		if (!data->env[i])
		{
			free_data(data);
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		i++;
		tmp = tmp->next;
	}
	data->env[i] = NULL;
}

void	add_env(t_data *data, const char *key, const char *value, int sign)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->sign = sign;
	new->next = data->envp;
	data->envp = new;
	data->env_len++;
}

void	init_env(t_data *data)
{
	int		i;
	char	*key;
	char	*value;
	char	*sign;

	data->envp = NULL;
	data->env_len = 0;
	i = 0;
	while (data->env[i])
	{
		sign = ft_strchr(data->env[i], '=');
		if (sign)
		{
			key = ft_strndup(data->env[i], sign - data->env[i]);
			value = ft_strdup(sign + 1);
			add_env(data, key, value, 0);
			free(key);
			free(value);
		}
		i++;
	}
	data->env = NULL;
}

t_envp	*env_find(t_envp *envp, const char *key)
{
	t_envp	*current;

	current = envp;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
