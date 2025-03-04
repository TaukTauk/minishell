/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:35:12 by talin             #+#    #+#             */
/*   Updated: 2025/03/04 15:37:41 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_data		data;
	int			i;
	t_command	*cmd;

	(void)ac;
	(void)av;
	init_shell(&data, env);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell > ");
		if (!input)
		{
			if (data.env)
				free_environ(data.env);
			break ;
		}
		if (*input)
			add_history(input);
		input[ft_strcspn(input, "\n")] = '\0';
		if (!ft_strcmp(input, "\0") || ft_is_only_space(input))
		{
			free(input);
			continue ;
		}
		gen_env(&data);
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
			if (!parameter_expansion(data.lexer, &data))
			{
				printf("EXPANSION ERROR!\n");
				free_lexer(data.lexer);
				free(input);
				continue ;
			}
			// parameter expansion done
			data.commands = parse_tokens(data.lexer, &data);
			// parsing done
			if (data.commands)
			{
				i = 0;
				cmd = data.commands;
				while (cmd)
				{
					i++;
					cmd = cmd->next;
				}
				data.cmd_count = i;
			}
			// print_commands(data.commands);
			if (!execute_commands(&data))
			{
				free_lexer(data.lexer);
				free(input);
				free_data(&data);
				break ;
			}
			free_command(data.commands);
			data.commands = NULL;
			free_lexer(data.lexer);
			data.lexer = NULL;
		}
		free(input);
	}
	free_data(&data);
	return (0);
}
