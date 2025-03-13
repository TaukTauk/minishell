/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:38:39 by talin             #+#    #+#             */
/*   Updated: 2025/03/13 11:04:21 by talin            ###   ########.fr       */
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
	if (tmp)
		free(tmp);
	// ft_printf("Freed IO File\n");
}

void	free_commands(t_command *cmd)
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
		if (cmd->redirections)
			ft_free_io_file(cmd->redirections);
		free(cmd);
		cmd = temp;
		// ft_printf("Freed Command\n");
	}
}

void	free_lexer(t_lexer *lexer)
{
	int	i;

	i = -1;
	while (++i < lexer->token_count)
		free(lexer->tokens[i]);
	free(lexer->tokens);
	lexer->tokens = NULL;
	free(lexer);
	// ft_printf("Freed Lexer\n");
}
