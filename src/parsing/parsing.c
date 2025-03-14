/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:27:03 by talin             #+#    #+#             */
/*   Updated: 2025/03/14 11:23:37 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	parse_tokens_delimeter(t_command *command_list, t_data *data)
{
	t_command		*tmp;
	t_redirection	*file;

	tmp = command_list;
	while (tmp)
	{
		if (tmp->redirections)
		{
			file = tmp->redirections;
			while (file)
			{
				if (file->type == REDIRECT_HEREDOC)
					delimeter_read(file, tmp, data);
				file = file->next;
			}
		}
		tmp = tmp->next;
	}
}

t_command	*parse_tokens(t_lexer *lexer, t_data *data)
{
	t_command	*command_list;
	t_command	*current_cmd;
	t_lexer		*current;

	if (!lexer)
		return (NULL);
	command_list = NULL;
	current_cmd = NULL;
	current = lexer;
	while (current)
	{
		if (!parse_tokens_statement(&command_list, &current_cmd, &current, data))
			return (NULL);
		current = current->next;
	}
	parse_tokens_delimeter(command_list, data);
	return (command_list);
}

void	print_commands(t_command *cmd)
{
	int			i;
	t_redirection	*tmp;

	while (cmd)
	{
		printf("Command: %s\n", cmd->cmd);
		if (cmd->args)
		{
			printf("Arguments:\n");
			i = -1;
			while (cmd->args[++i])
				printf("  %s\n", cmd->args[i]);
		}
		if (cmd->redirections)
		{
			tmp = cmd->redirections;
			while (tmp)
			{
				if (tmp->type == REDIRECT_INPUT)
					printf("Input file:");
				else if (tmp->type == REDIRECT_OUTPUT)
					printf("Output file:");
				else if (tmp->type == REDIRECT_HEREDOC)
					printf("Heredoc:");
				else if (tmp->type == REDIRECT_APPEND)
					printf("Output file append:");
				printf(" %s (Type: %d), order number ==> %d\n", \
				tmp->file_name, tmp->type, tmp->order_value);
				if (tmp->content)
					printf("%s", tmp->content);
				tmp = tmp->next;
			}
		}
		printf("Input order : %d\n", cmd->input_order);
		printf("Output order : %d\n", cmd->output_order);
		cmd = cmd->next;
		printf("\n");
	}
}
