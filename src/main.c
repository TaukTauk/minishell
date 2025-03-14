/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:35:12 by talin             #+#    #+#             */
/*   Updated: 2025/03/14 11:51:43 by talin            ###   ########.fr       */
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

void	print_tokens(t_lexer *lexer)
{
	t_lexer	*current;

	if (!lexer)
		return ;
	current = lexer;
	while (current)
	{
		if (current->value)
		{
			printf("[{%s}, ", current->value);
			if (current->token_type == TKN_IN)
				printf("{type: %s}] ", "infile");
			else if (current->token_type == TKN_OUT)
				printf("{type: %s}] ", "outfile");
			else if (current->token_type == TKN_RDAPPEND)
				printf("{type: %s}] ", "outfileappend");
			else if (current->token_type == TKN_RDHEREDOC)
				printf("{type: %s}] ", "heredoc");
			else if (current->token_type == TKN_WORD)
				printf("{type: %s}] ", "word");
			else if (current->token_type == TKN_PIPE)
				printf("{type: %s}] ", "pipe");
			printf("\n");
		}
		current = current->next;
	}
}

int	handle_command_input(char *input, t_data *data)
{
	if (!input || !*input)
		return (1);
	if (*input)
		add_history(input);
	input[ft_strcspn(input, "\n")] = '\0';
	data->lexer = tokenize(input, data);
	// print_tokens(data->lexer);
	if (!data->lexer)
	{
		ft_printf("DEBUG: Tokenization failed\n");
		return (1);
	}
	if (sanitize_tokens(data->lexer, data))
	{
		ft_printf("DEBUG: Token sanitization failed\n");
		// free_lexer(data->lexer);
		return (1);
	}
	if (!parameter_expansion(data->lexer, data))
	{
		ft_printf("DEBUG: Parameter expansion failed\n");
		// free_lexer(data->lexer);
		return (1);
	}
	data->commands = parse_tokens(data->lexer, data);
	if (!data->commands)
	{
		// ft_printf("DEBUG: Parsing tokens failed\n");
		// free_lexer(data->lexer);
		return (1);
	}
	data->cmd_count = count_commands(data);
	// print_commands(data->commands);
	execute_commands(data);
	// free_data(data);
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
	(void)env;
	init_shell(&data, env);
	while (1)
	{
		g_delim_interrupt = 0;
		gen_env(&data);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell > ");
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
		free(input);
	}
	free_env(&data);
	rl_clear_history();
	free(data.envp);
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
