/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:36:35 by rick              #+#    #+#             */
/*   Updated: 2025/03/03 10:47:02 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	export_env(t_envp **envp, char *arg, t_data **data)
{
    t_envp	*current;
    t_envp	*new_node;
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
            return ;
        }
        current = current->next;
    }
    new_node = malloc(sizeof(t_envp));
    if (!new_node)
    {
        perror("malloc");
        free(key);
        free(value);
        return;
    }
    new_node->key = key;
    new_node->value = value;
    new_node->sign = 1;
    new_node->next = *envp;
    *envp = new_node;
	(*data)->env_len++;
}


void unset_env(t_envp **envp, char *key, t_data **data)
{
    t_envp *current = *envp;
    t_envp *prev = NULL;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *envp = current->next;
            free(current->key);
            free(current->value);
            free(current);
			(*data)->env_len--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

int	execute_builtin(t_command *commands, t_data *data)
{
	int i;

	if (ft_strcmp(commands->cmd, "env") == 0)
	{
		i = -1;
		while (data->env[++i])
			printf("%s\n", data->env[i]);
		data->status = 0;
		return (1);
	}
	else if (ft_strcmp(commands->cmd, "echo") == 0)
	{
		ft_echo(commands, data);
		return (1);
	}
	else if (ft_strcmp(commands->cmd, "cd") == 0)
	{
		ft_cd(commands, data);
		return (1);
	}
	else if (ft_strcmp(commands->cmd, "pwd") == 0)
	{
		char *buf;
		buf = getcwd(NULL, 0);
		if (buf != NULL) {
			printf("%s\n", buf);
			free(buf);
		} else {
			perror("getcwd");
		}
		return (1);
	}
	else if (ft_strcmp(commands->cmd, "export") == 0)
	{
		if (commands->args[1])
		{
			i = 0;
			while (commands->args[++i])
			{
				if (commands->args[i])
				{ 
					export_env(&(data->envp), commands->args[i], &data);
				}
			}
		}
		else
		{
			t_envp	*current;
			current = data->envp;
			while (current)
			{
				printf("declare -x ");
				printf("%s=\"%s\"\n", current->key, current->value);
				current = current->next;
			}
		}
		return (1);
	}
	else if (ft_strcmp(commands->cmd, "unset") == 0)
	{
		if (commands->args[1])
		{
			i = 0;
			while (commands->args[++i])
			{
				if (commands->args[i])
				{ 
					unset_env(&(data->envp), commands->args[i], &data);
				}
			}
		}
		return (1);
	}
	else if (ft_strcmp(commands->cmd, "exit") == 0)
	{
		ft_exit(commands, data);
		return (1);
	}
	return (1);
}
