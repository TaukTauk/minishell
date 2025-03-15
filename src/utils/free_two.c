/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:19:18 by talin             #+#    #+#             */
/*   Updated: 2025/03/15 22:30:27 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_io_file(t_redirection *file)
{
	t_redirection	*tmp;

	if (file)
	{
		while (file)
		{
			tmp = file;
			file = file->next;
			if (tmp->file_name)
				free(tmp->file_name);
			if (tmp->content)
				free(tmp->content);
			free(tmp);
		}
	}
	// ft_printf("Freed IO File\n");
}

void	free_command(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	if (cmd)
	{
		while (cmd)
		{
			tmp = cmd;
			cmd = cmd->next;
			if (tmp->cmd)
				free(tmp->cmd);
			if (tmp->args)
			{
				i = 0;
				while (tmp->args[i])
					free(tmp->args[i++]);
				free(tmp->args);
			}
			if (tmp->redirections)
				free_io_file(tmp->redirections);
			free(tmp);
		}
	}
	// printf("Freed command\n");
}

void	free_envp(t_envp *envp)
{
	t_envp	*tmp;

	while (envp)
	{
		tmp = envp;
		envp = envp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	// ft_printf("Freed ENVP\n");
}

void	free_data(t_data *data)
{
	if (data->commands)
		free_commands(data->commands);
	free_env(data);
	data->envp = NULL;
	data->commands = NULL;
	data->lexer = NULL;
}
