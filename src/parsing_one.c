/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:36:53 by talin             #+#    #+#             */
/*   Updated: 2025/03/02 10:39:05 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_io_file(t_io_file **file_list, char *file_name, int redirect_type, int order_num)
{
	t_io_file	*new_file;
	t_io_file	*last;

	if (!file_name)
		return (0);

	new_file = malloc(sizeof(t_io_file));
	if (!new_file)
		return (0);
	new_file->file_name = ft_strdup(file_name);
	if (!new_file->file_name)
	{
		free(new_file);
		return (0);
	}
	new_file->redirect_type = redirect_type;
	new_file->order_value = order_num;
	new_file->content = NULL;
	new_file->next = NULL;

	if (!(*file_list))
		*file_list = new_file;
	else
	{
		last = *file_list;
		while (last->next)
			last = last->next;
		last->next = new_file;
	}
	return (1);
}

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->outfileappend = NULL;
	cmd->delimeter = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->builtin = 0;
	cmd->input_order = 0;
	cmd->output_order = 0;
	cmd->next = NULL;
	return (cmd);
}

int	add_argument(t_command *cmd, char *arg)
{
	int		arg_count;
	char	**new_args;
	int		i;

	arg_count = 0;
	if (!arg)
		return (0);
	if (cmd->args)
		while (cmd->args[arg_count])
			arg_count++;
	new_args = malloc(sizeof(char *) * (arg_count + 2));
	if (!new_args)
		return (0);
	i = -1;
	while (++i < arg_count)
		new_args[i] = cmd->args[i];
	free(cmd->args);
	new_args[arg_count] = ft_strdup(arg);
	if (!new_args[arg_count])
		return (free(new_args), 0);
	new_args[arg_count + 1] = NULL;
	(cmd->args = new_args);
	return (1);
}

int	ft_parse_pipe(t_command **command_list, t_command **current_cmd)
{
	if (!*current_cmd)
	{
		perror("Syntax error: Pipe '|' without a preceding command");
		return (free_commands(*command_list), 0);
	}
	(*current_cmd)->next = create_command();
	if (!(*current_cmd)->next)
	{
		perror("Error: Failed to allocate memory for command");
		return (free_commands(*command_list), 0);
	}
	(*current_cmd) = (*current_cmd)->next;
	return (1);
}

int	ft_parse_in_red_two(t_command **command_list, \
	t_command **current_cmd, int *i, t_data *data)
{
	char	*token;

	token = data->lexer->tokens[*i];
	if (ft_strcmp(token, "<") == 0)
	{
		if (!create_io_file(&(*current_cmd)->infile, data->lexer->tokens[++(*i)], REDIRECT_INPUT, ++(*current_cmd)->input_order))
		{
			perror("Error: malloc for input redirection file");
			return (free_commands(*command_list), 0);
		}
	}
	else
	{
		if (!create_io_file(&(*current_cmd)->delimeter, data->lexer->tokens[++(*i)], REDIRECT_HEREDOC, ++(*current_cmd)->input_order))
		{
			perror("Error: malloc for delimiter");
			return (free_commands(*command_list), 0);
		}
	}
	return (1);
}
