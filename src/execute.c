/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:22:58 by talin             #+#    #+#             */
/*   Updated: 2025/02/24 16:42:10 by talin            ###   ########.fr       */
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

void	ft_free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*ft_getenv(char *name, char **envp)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		str = ft_substr(envp[i], 0, j);
		if (ft_strcmp(str, name) == 0)
		{
			free(str);
			return (envp[i] + j + 1);
		}
		free(str);
		i++;
	}
	return (NULL);
}

int	ft_check_set_unset(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 5) == 0 && envp[i][5] == '=')
			return (1);
	}
	return (0);
}

char	*ft_get_path(char *cmd, char **envp, int i)
{
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	if (ft_check_set_unset(envp) == 0)
		return (cmd);
	allpath = ft_split(ft_getenv("PATH", envp), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_arr(allpath);
			ft_free_arr(s_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_arr(allpath);
	ft_free_arr(s_cmd);
	return (cmd);
}

void	execve_cmd(char *cmd, char **s_cmd, char **envp)
{
	char *path;
	(void)cmd;

	path = ft_get_path(s_cmd[0], envp, -1);
	if (execve(path, s_cmd, envp) == -1)
	{
		if (access(path, F_OK) == 0)
			ft_putstr_fd("permission denied: ", 2);
		else
			ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
	}
}

int	execute_commands(t_data *data)
{
	int	i;

	if (data->commands->cmd)
	{
		if (ft_strcmp(data->commands->cmd, "env") == 0)
		{
			i = -1;
			while (data->env[++i])
			{
				printf("%s\n", data->env[i]);
			}
		}
		else if (ft_strcmp(data->commands->cmd, "echo") == 0)
		{
			i = 0;
			while (data->commands->args[++i])
			{
				if (ft_strcmp(data->commands->args[i], "-n") == 0)
					continue ;
				printf("%s", data->commands->args[i]);
				if (data->commands->args[i + 1])
					printf(" ");
			}
			if (ft_strcmp(data->commands->args[1], "-n") != 0)
				printf("\n");
		}
		else if (ft_strcmp(data->commands->cmd, "cd") == 0)
		{
			if (data->commands->args[1])
			{
				if (data->commands->args[2])
					perror("too many arguments");
				else 
				{
					if (chdir(data->commands->args[1]) != 0)
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
		}
		else if (ft_strcmp(data->commands->cmd, "pwd") == 0)
		{
			char *buf;
			buf = getcwd(NULL, 0);
			if (buf != NULL) {
				printf("%s\n", buf);
				free(buf);
			} else {
				perror("getcwd");
			}
		}
		else if (ft_strcmp(data->commands->cmd, "export") == 0)
		{
			if (data->commands->args[1])
			{
				i = 0;
				while (data->commands->args[++i])
				{
					if (data->commands->args[i])
					{ 
						export_env(&(data->env), data->commands->args[i]);
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
		}
		else if (ft_strcmp(data->commands->cmd, "unset") == 0)
		{
			if (data->commands->args[1])
			{
				i = 0;
				while (data->commands->args[++i])
				{
					if (data->commands->args[i])
					{ 
						unset_env(data->env, data->commands->args[i]);
					}
				}
			}
		}
		else if (ft_strcmp(data->commands->cmd, "exit") == 0)
			return (0);
		else
		{
			execve_cmd(data->commands->cmd, data->commands->args, data->env);
		}
	}
	return (1);
}
