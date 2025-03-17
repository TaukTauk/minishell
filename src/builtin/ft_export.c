/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:12:01 by talin             #+#    #+#             */
/*   Updated: 2025/03/17 11:08:13 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	export_env_util(t_data **data, char *key, char *value, char *arg)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	(*data)->status = 1;
	if (key)
		free(key);
	if (value)
		free(value);
}

static void	ft_equal(char **key, char **value, char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*key = ft_strndup(arg, equal_sign - arg);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = strdup(arg);
		*value = NULL;
	}
}

static void	export_env(t_envp **envp, char *arg, t_data **data)
{
	t_envp	*current;
	char	*key;
	char	*value;

	ft_equal(&key, &value, arg);
	if (!is_valid_variable_name(key))
	{
		export_env_util(data, key, value, arg);
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
