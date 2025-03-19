/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:01:12 by juhtoo-h          #+#    #+#             */
/*   Updated: 2025/03/19 14:33:43 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export_env_search(t_envp *current, char *key, char *value)
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

int	export_env_new(char *key, char *value, t_envp **envp, t_data **data)
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

int	is_valid_variable_name(const char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!((name[0] >= 'a' && name[0] <= 'z')
			|| (name[0] >= 'A' && name[0] <= 'Z') || name[0] == '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!((name[i] >= 'a' && name[i] <= 'z')
				|| (name[i] >= 'A' && name[i] <= 'Z')
				|| (name[i] >= '0' && name[i] <= '9')
				|| name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
