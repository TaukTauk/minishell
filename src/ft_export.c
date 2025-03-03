/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:12:01 by talin             #+#    #+#             */
/*   Updated: 2025/03/03 15:13:10 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	export_env_search(t_envp *current, char *key, char *value)
{
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			if (value)
			{
				free(current->value);
				current->value = strdup(value);
			}
			free(key);
			free(value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

static int	export_env_new(char *key, char *value, t_envp **envp, t_data **data)
{
	t_envp	*new_node;

	new_node = malloc(sizeof(t_envp));
	if (!new_node)
	{
		perror("malloc");
		free(key);
		free(value);
		return (0);
	}
	new_node->key = key;
	new_node->value = value;
	new_node->sign = 1;
	new_node->next = *envp;
	*envp = new_node;
	(*data)->env_len++;
	return (1);
}

static void	export_env(t_envp **envp, char *arg, t_data **data)
{
	t_envp	*current;
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key = ft_strndup(arg, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
	}
	else
	{
		key = strdup(arg);
		value = NULL;
	}
	current = *envp;
	if (export_env_search(current, key, value))
		return ;
	if (!export_env_new(key, value, envp, data))
		return ;
}

void	ft_export(t_command *commands, t_data *data)
{
	int		i;
	t_envp	*current;

	if (commands->args[1])
	{
		i = 0;
		while (commands->args[++i])
		{
			if (commands->args[i])
				export_env(&(data->envp), commands->args[i], &data);
		}
	}
	else
	{
		current = data->envp;
		while (current)
		{
			printf("declare -x ");
			printf("%s=\"%s\"\n", current->key, current->value);
			current = current->next;
		}
	}
}
