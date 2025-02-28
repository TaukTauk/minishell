/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:35:12 by talin             #+#    #+#             */
/*   Updated: 2025/02/28 15:13:16 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	*tokenize(char *input)
{
	t_lexer	*lexer;
	char	**new_tokens;
	int		i;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->tokens = NULL;
	lexer->token_count = 0;
	if (!ft_tokenize_four(lexer, input))
		return (NULL);
	new_tokens = malloc(sizeof(char *) * (lexer->token_count + 1));
	if (!new_tokens)
		return (free_lexer(lexer), NULL);
	i = -1;
	while (++i < lexer->token_count)
		new_tokens[i] = lexer->tokens[i];
	free(lexer->tokens);
	lexer->tokens = new_tokens;
	lexer->tokens[lexer->token_count] = NULL;
	return (lexer);
}

void	free_data(t_data *data)
{
	int	i;

	if (data)
	{
		if (data->commands)
		{
			free_commands(data->commands);
		}
		if (data->env)
		{
			i = -1;
			while (data->env[++i])
				free(data->env[i]);
			free(data->env);
		}
	}
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

void	free_environ(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_env(t_data *data)
{
	t_envp	*temp;

	while (data->envp)
	{
		temp = data->envp;
		data->envp = data->envp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	free_environ(data->env);
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

void	update_shlvl(t_data *data)
{
	t_envp	*temp;
	int		num;

	temp = env_find(data->envp, "SHLVL");
	if (temp)
	{
		num = ft_atoi(temp->value);
		num++;
		free(temp->value);
		temp->value = ft_itoa(num);
		if (!temp->value)
		{
			perror("ft_itoa");
			exit(EXIT_FAILURE);
		}
	}
}

char	*ft_multjoin(char **arr_str)
{
	char	*res;
	char	*tmp;

	if (!arr_str && !*arr_str)
		return (NULL);
	res = ft_strdup(*arr_str++);
	while (*arr_str)
	{
		tmp = ft_strjoin(res, *arr_str);
		free(res);
		res = tmp;
		arr_str++;
	}
	return (tmp);
}

void	gen_env(t_data *data)
{
	t_envp	*tmp;
	size_t	i;

	if (data->env != NULL)
		free_environ(data->env);
	i = 0;
	data->env = malloc(sizeof(*data->env) * (data->env_len + 1));
	tmp = data->envp;
	while (tmp)
	{
		data->env[i++] = ft_multjoin((char *[]){tmp->key, "=", tmp->value,
				NULL});
		tmp = tmp->next;
	}
	data->env[i] = NULL;
}

void	init_shell(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(*data));
	data->env = envp;
	data->status = 0;
	init_env(data);
	update_shlvl(data);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_data		data;
	int			i;
	(void)ac;
	(void)av;

	init_shell(&data, env);
	while (1)
	{
		gen_env(&data);
		input = readline("minishell > ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		input[ft_strcspn(input, "\n")] = '\0';
		data.lexer = tokenize(input);
		if (data.lexer)
		{
			// tokenization done but need to handle for meta-characters
			if (sanitize_tokens(data.lexer->tokens) != 0)
			{
				printf("SANITIZATION ERROR!\n");
				free_lexer(data.lexer);
				free(input);
				continue ;
			}
			// sanitization done 
			if (!parameter_expansion(data.lexer, data.env))
			{
				printf("EXPANSION ERROR!\n");
				free_lexer(data.lexer);
				free(input);
				continue ;
			}
			// parameter expansion done
			data.commands = parse_tokens(data.lexer, &data);
			// print_commands(data.commands);
			// parsing done
			if (data.commands) {
				i = 0;
				t_command *cmd = data.commands;
				while (cmd)
				{
					i++;
					cmd = cmd->next;
				}
				data.cmd_count = i;
				// free_commands(data.commands);
			}
			if (!execute_commands(&data))
			{
				// free_lexer(data.lexer);
				free(input);
				// free_data(&data);
				break ;
			}
			free_lexer(data.lexer);
		}
		free(input);
	}
	return (0);
}
