/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:38:39 by talin             #+#    #+#             */
/*   Updated: 2025/03/15 20:34:03 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_io_file(t_redirection *file)
{
	t_redirection	*tmp;
	t_redirection	*next;

	if (!file)
		return ;
	tmp = file;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->file_name)
			free(tmp->file_name);
		if (tmp->content)
			free(tmp->content);
		if (tmp)
			free(tmp);
		tmp = next;
	}
}

void	free_commands(t_command *cmd)
{
	t_command	*temp;
	int			i;

	if (!cmd)
		return ;
	while (cmd)
	{
		temp = cmd->next;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->args)
		{
			i = -1;
			while (cmd->args[++i])
			{
				if (cmd->args[i])
					free(cmd->args[i]);
			}
			free(cmd->args);
		}
		if (cmd->redirections)
			ft_free_io_file(cmd->redirections);
		free(cmd);
		cmd = temp;
	}
	cmd = NULL;
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;
	t_lexer	*next;

	if (!lexer)
		return ;
	tmp = lexer;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->value)
			free(tmp->value);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		tmp = next;
	}
	lexer = NULL;
}
