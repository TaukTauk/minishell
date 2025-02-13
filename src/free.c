/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:38:39 by talin             #+#    #+#             */
/*   Updated: 2025/01/16 10:40:03 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_io_file(t_io_file *file)
{
	free(file->file_name);
	free(file);
}

void	free_commands(t_command *cmd)
{
	t_command	*temp;
	int			i;

	while (cmd)
	{
		temp = cmd;
		if (temp->cmd)
			free(temp->cmd);
		if (temp->args)
		{
			i = -1;
			while (temp->args[++i])
				free(temp->args[i]);
			free(temp->args);
		}
		if (temp->infile)
			ft_free_io_file(temp->infile);
		if (temp->outfile)
			ft_free_io_file(temp->outfile);
		free(temp);
		cmd = cmd->next;
	}
}

void	free_lexer(t_lexer *lexer)
{
	int	i;

	i = -1;
	while (++i < lexer->token_count)
		free(lexer->tokens[i]);
	free(lexer->tokens);
	free(lexer);
}
