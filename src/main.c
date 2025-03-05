/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:35:12 by talin             #+#    #+#             */
/*   Updated: 2025/03/05 14:07:08 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	data->lexer = tokenize(input);
	if (!data->lexer)
	{
		printf("DEBUG: Tokenization failed\n");
		return (1);
	}
	if (sanitize_tokens(data->lexer->tokens))
	{
		printf("DEBUG: Token sanitization failed\n");
		free_lexer(data->lexer);
		return (1);
	}
	if (!parameter_expansion(data->lexer, data))
	{
		printf("DEBUG: Parameter expansion failed\n");
		free_lexer(data->lexer);
		return (1);
	}
	data->commands = parse_tokens(data->lexer, data);
	if (!data->commands)
	{
		printf("DEBUG: Parsing tokens failed\n");
		free_lexer(data->lexer);
		return (1);
	}
	data->cmd_count = count_commands(data);
	// print_commands(data->commands);
	execute_commands(data);
	// Cleanup
	// free_data(data);
	free(input);
	return (1);
}

// int	handle_command_input(char *input, t_data *data)
// {
// 	if (*input && input)
// 		add_history(input);
// 	input[ft_strcspn(input, "\n")] = '\0';
// 	data->lexer = tokenize(input);
// 	if (sanitize_tokens(data->lexer->tokens))
// 		return (free_lexer(data->lexer), 1);
// 	if (!parameter_expansion(data->lexer, data))
// 		return (free_lexer(data->lexer), 1);
// 	data->commands = parse_tokens(data->lexer, data);
// 	if (!data->commands)
// 		return (free_lexer(data->lexer), 1);
// 	data->cmd_count = count_commands(data);
// 	execute_commands(data);
// 	free_data(data);
// 	free(input);
// 	return (1);
// }

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	data;

	(void)ac;
	(void)av;
	init_shell(&data, env);
	// Ensure clean signal handling
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		gen_env(&data);
		// Reinitialize signals for each iteration
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell > ");
		// Reset signals before processing input
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		if (!input)
		{
			printf("DEBUG: Received NULL input\n");
			free_env(&data);
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (handle_command_input(input, &data) < 0)
		{
			printf("DEBUG: handle_command_input returned < 0\n");
			break ;
		}
	}
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	char		*input;
// 	t_data		data;

// 	(void)ac;
// 	(void)av;
// 	init_shell(&data, env);
// 	while (1)
// 	{
// 		gen_env(&data);
// 		signal(SIGINT, handle_sigint);
// 		signal(SIGQUIT, SIG_IGN);
// 		input = readline("minishell > ");
// 		if (!input)
// 		{
// 			free_env(&data);
// 			ft_putendl_fd("exit", STDOUT_FILENO);
// 			break ;
// 		}
// 		if (handle_command_input(input, &data) < 0)
// 			break ;
// 	}
// 	free_env(&data);
// 	return (0);
// }
