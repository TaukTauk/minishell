/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:35:12 by talin             #+#    #+#             */
/*   Updated: 2025/03/19 21:38:56 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_delim_interrupt = 0;

int	count_commands(t_data *data)
{
	int			count;
	t_command	*current;

	current = data->commands;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	handle_command_input(char *input, t_data *data)
{
	if (!input || !*input)
		return (1);
	if (*input)
		add_history(input);
	input[ft_strcspn(input, "\n")] = '\0';
	if (g_delim_interrupt)
	{
		data->status = 130;
		g_delim_interrupt = 0;
	}
	data->lexer = tokenize(input, data);
	if (!data->lexer)
		return (1);
	if (sanitize_tokens(data->lexer, data))
		return (1);
	if (!parameter_expansion(&(data->lexer), data))
		return (1);
	data->commands = parse_tokens(data->lexer, data);
	if (!data->commands)
		return (1);
	data->cmd_count = count_commands(data);
	execute_commands(data);
	free_commands(data->commands);
	return (1);
}

static void	minishell(t_data *data)
{
	char	*input;

	while (1)
	{
		g_delim_interrupt = 0;
		gen_env(data);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell $ ");
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (handle_command_input(input, data) < 0)
		{
			free(input);
			break ;
		}
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_shell(&data, env);
	minishell(&data);
	free_env(&data);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
