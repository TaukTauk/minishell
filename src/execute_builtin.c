/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:36:35 by rick              #+#    #+#             */
/*   Updated: 2025/02/28 09:39:52 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **realloc_env(char **env, int size)
{
    char **new_env;
    int i;

    new_env = malloc(sizeof(char *) * (size + 1));
    if (!new_env)
        return (NULL);
    i = -1;
    while (env[++i])
    {
        new_env[i] = ft_strdup(env[i]);
        if (!new_env[i])
        {
            while (--i >= 0)
                free(new_env[i]);
            free(new_env);
            return (NULL);
        }
    }
    new_env[i] = NULL;
    return (new_env);
}

int is_valid_identifier(const char *str)
{
    int i;

    if (!str || !*str || ft_isdigit(*str))
        return (0);
    i = 0;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

void export_env(char ***env, char *var)
{
    int i;
    char *equal_sign;
    int var_len;
    char **new_env;

    if (!is_valid_identifier(var))
    {
        ft_putstr_fd("export: not a valid identifier\n", 2);
        return;
    }
    equal_sign = ft_strchr(var, '=');
    if (equal_sign)
        var_len = equal_sign - var;
    else
        var_len = ft_strlen(var);
    i = -1;
    while ((*env)[++i])
    {
        if (ft_strncmp((*env)[i], var, var_len) == 0 && 
            ((*env)[i][var_len] == '=' || (*env)[i][var_len] == '\0'))
        {
            if (equal_sign)
            {
                char *tmp = ft_strdup(var);
                if (!tmp)
                    return;
                free((*env)[i]);
                (*env)[i] = tmp;
            }
            return;
        }
    }
    if (equal_sign)
    {
        new_env = realloc_env(*env, i + 1);
        if (!new_env)
            return;
        new_env[i] = ft_strdup(var);
        if (!new_env[i])
        {
            free(new_env);
            return;
        }
        new_env[i + 1] = NULL;
        i = -1;
        while ((*env)[++i])
            free((*env)[i]);
        free(*env);
        
        *env = new_env;
    }
}

void unset_env(char **env, char *var)
{
    int i;
    int var_len;

    if (!is_valid_identifier(var))
    {
        ft_putstr_fd("unset: not a valid identifier\n", 2);
        return;
    }

    var_len = ft_strlen(var);
    i = -1;
    while (env[++i])
    {
        if (ft_strncmp(env[i], var, var_len) == 0 && 
            (env[i][var_len] == '=' || env[i][var_len] == '\0'))
        {
            free(env[i]);
            while (env[i + 1])
            {
                env[i] = env[i + 1];
                i++;
            }
            env[i] = NULL;
            return;
        }
    }
}

int	execute_builtin(t_command *commands, t_data *data)
{
	int i;

	if (ft_strcmp(commands->cmd, "env") == 0)
	{
		i = -1;
		while (data->env[++i])
		{
			printf("%s\n", data->env[i]);
		}
		return (1);
	}
	else if (ft_strcmp(commands->cmd, "echo") == 0)
	{
		i = 0;
		while (commands->args[++i])
		{
			if (ft_strcmp(commands->args[i], "-n") == 0)
				continue ;
			printf("%s", commands->args[i]);
			if (commands->args[i + 1])
				printf(" ");
		}
		if (ft_strcmp(commands->args[1], "-n") != 0)
			printf("\n");
		return (1);
	}
	else if (ft_strcmp(commands->cmd, "cd") == 0)
	{
		if (commands->args[1])
		{
			if (commands->args[2])
				perror("too many arguments");
			else 
			{
				if (chdir(commands->args[1]) != 0)
				perror("chdir() failed");
			}
		}
		else
		{
			char	*home;

			i = -1;
			home = NULL;
			while (data->env[++i])
			{
				if (ft_strncmp("HOME=", data->env[i], 5) == 0)
				{
					home = ft_strdup(data->env[i] + 5);
					break ;
				}
			}
			if (home)
			{
				if (chdir(home) != 0)
				perror("chdir() failed");
			}
			
		}
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
					export_env(&(data->env), commands->args[i]);
				}
			}
		}
		else
		{
			i = -1;
			int j;
			while (data->env[++i])
			{
				printf("declare -x ");
				j = -1;
				while (data->env[i][++j])
				{
					printf("%c", data->env[i][j]);
					if (data->env[i][j] == '=')
						printf("\"");
				}
				printf("\"\n");
				
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
					unset_env(data->env, commands->args[i]);
				}
			}
		}
		return (1);
	}
	else if (ft_strcmp(commands->cmd, "exit") == 0)
		return (0);
	return (1);
}
