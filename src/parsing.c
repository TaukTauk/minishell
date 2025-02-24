/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:27:03 by talin             #+#    #+#             */
/*   Updated: 2025/02/24 10:32:41 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*parse_tokens(t_lexer *lexer)
{
	t_command	*command_list;
	t_command	*current_cmd;
	int			i;

	command_list = NULL;
	current_cmd = NULL;
	i = -1;
	while (++i < lexer->token_count)
	{
		if (!parse_tokens_statement(&command_list, &current_cmd, &i, lexer))
			return (NULL);
	}
	return (command_list);
}

void	print_commands(t_command *cmd)
{
	int	i;

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
		if (cmd->infile)
			printf("Input File: %s (Type: %d)\n", \
			cmd->infile->file_name, cmd->infile->redirect_type);
		if (cmd->outfile)
			printf("Output File: %s (Type: %d)\n", \
			cmd->outfile->file_name, cmd->outfile->redirect_type);
		cmd = cmd->next;
		printf("\n");
	}
}
