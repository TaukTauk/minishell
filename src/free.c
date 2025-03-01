/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:38:39 by talin             #+#    #+#             */
/*   Updated: 2025/03/01 21:05:02 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_free_io_file(t_io_file *file)
{
    if (!file)
        return ;
    if (file->file_name)
        free(file->file_name);
    free(file);
}

void free_commands(t_command *cmd)
{
	t_command	*temp;
	int			i;

	while (cmd)
	{
		temp = cmd->next;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->args)
		{
			i = -1;
			while (cmd->args[++i])
				free(cmd->args[i]);
			free(cmd->args);
		}
		if (cmd->infile)
			ft_free_io_file(cmd->infile);
		if (cmd->outfile)
			ft_free_io_file(cmd->outfile);
		if (cmd->delimeter)
			ft_free_io_file(cmd->delimeter);
		free(cmd);
		cmd = temp;
	}
}

void free_lexer(t_lexer *lexer)
{
    int i;
    
    i = -1;
    while (++i < lexer->token_count)
        free(lexer->tokens[i]);
    free(lexer->tokens);
    lexer->tokens = NULL;
    free(lexer);
}
