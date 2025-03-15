/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:12:01 by talin             #+#    #+#             */
/*   Updated: 2025/03/15 20:15:44 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static int is_valid_variable_name(const char *name)
{
	int	i;
    
	if (!name || !*name)
		return (0);
	if (!((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z') || name[0] == '_'))
        return (0);
	i = 1;
	while (name[i])
	{
		if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= '0' && name[i] <= '9') || name[i] == '_'))
            return (0);
		i++;
	}
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
	if (!is_valid_variable_name(key))
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		(*data)->status = 1;
		if (key)
			free(key);
		if (value)
			free(value);
		return ;
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
