/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:35:12 by talin             #+#    #+#             */
/*   Updated: 2025/03/17 14:46:05 by juhtoo-h         ###   ########.fr       */
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
		input = readline("minishell > ");
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

// void	print_tokens(t_lexer *lexer)
// {
// 	t_lexer	*current;

// 	if (!lexer)
// 		return ;
// 	current = lexer;
// 	while (current)
// 	{
// 		if (current->value)
// 		{
// 			printf("[{%s}, ", current->value);
// 			if (current->token_type == TKN_IN)
// 				printf("{type: %s}] ", "infile");
// 			else if (current->token_type == TKN_OUT)
// 				printf("{type: %s}] ", "outfile");
// 			else if (current->token_type == TKN_RDAPPEND)
// 				printf("{type: %s}] ", "outfileappend");
// 			else if (current->token_type == TKN_RDHEREDOC)
// 				printf("{type: %s}] ", "heredoc");
// 			else if (current->token_type == TKN_WORD)
// 				printf("{type: %s}] ", "word");
// 			else if (current->token_type == TKN_PIPE)
// 				printf("{type: %s}] ", "pipe");
// 			printf("\n");
// 		}
// 		current = current->next;
// 	}
// }