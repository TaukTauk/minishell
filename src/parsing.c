/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:27:03 by talin             #+#    #+#             */
/*   Updated: 2025/03/02 12:29:47 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*parse_tokens(t_lexer *lexer, t_data *data)
{
	t_command	*command_list;
	t_command	*current_cmd;
	t_command	*tmp;
	int			i;

	command_list = NULL;
	current_cmd = NULL;
	i = -1;
	while (++i < lexer->token_count)
	{
		if (!parse_tokens_statement(&command_list, &current_cmd, &i, data))
			return (NULL);
	}
	tmp = command_list;
	while (tmp)
	{
		if (tmp->delimeter)
		{
			t_io_file	*file;
			file = tmp->delimeter;
			while (file)
			{
				delimeter_read(file, tmp, data);
				file = file->next;
			}
		}
		tmp = tmp->next;
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
		t_io_file *tmp;
		if (cmd->infile)
		{
			tmp = cmd->infile;
			while (tmp)
			{
				printf("Input File: %s (Type: %d), order number ==> %d\n", \
				tmp->file_name, tmp->redirect_type, tmp->order_value);
				tmp = tmp->next;
			}
		}
		if (cmd->outfile)
		{
			tmp = cmd->outfile;
			while (tmp)
			{
				printf("Output File: %s (Type: %d), order number ==> %d\n", \
				tmp->file_name, tmp->redirect_type, tmp->order_value);
				tmp = tmp->next;
			}
		}
		if (cmd->outfileappend)
		{
			tmp = cmd->outfileappend;
			while (tmp)
			{
				printf("Output append File: %s (Type: %d), order number ==> %d\n", \
				tmp->file_name, tmp->redirect_type, tmp->order_value);
				tmp = tmp->next;
			}
		}
		if (cmd->delimeter)
		{
			tmp = cmd->delimeter;
			while (tmp)
			{
				printf("Delimeter: %s (Type: %d), order number ==> %d\n", \
				tmp->file_name, tmp->redirect_type, tmp->order_value);
				printf("Content.......... \n");
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
