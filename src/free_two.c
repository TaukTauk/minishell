/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:19:18 by talin             #+#    #+#             */
/*   Updated: 2025/03/04 12:29:59 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_io_file(t_io_file *file)
{
	t_io_file	*tmp;

	while (file)
	{
		tmp = file;
		file = file->next;
		free(tmp->file_name);
		free(tmp->content);
		free(tmp);
	}
}

void	free_command(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp->cmd);
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
				free(tmp->args[i++]);
			free(tmp->args);
		}
		free_io_file(tmp->infile);
		free_io_file(tmp->outfile);
		free_io_file(tmp->delimeter);
		free_io_file(tmp->outfileappend);
		free(tmp);
	}
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
}

void	free_data(t_data *data)
{
	int	i;

	if (data->env)
	{
		i = 0;
		while (data->env[i])
			free(data->env[i++]);
		free(data->env);
	}
	free_command(data->commands);
	free_envp(data->envp);
	data->commands = NULL;
	data->envp = NULL;
	data->env = NULL;
	data->lexer = NULL;
}
