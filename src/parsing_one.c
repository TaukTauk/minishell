/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:36:53 by talin             #+#    #+#             */
/*   Updated: 2025/02/24 11:57:41 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_io_file	*create_io_file(char *file_name, int redirect_type)
{
	t_io_file	*file;

	if (!file_name)
		return (NULL);
	file = malloc(sizeof(t_io_file));
	if (!file)
		return (NULL);
	file->file_name = ft_strdup(file_name);
	if (!file->file_name)
		return (free(file), NULL);
	file->redirect_type = redirect_type;
	return (file);
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
	cmd->delimeter = NULL;
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
t_command **current_cmd, int *i, t_lexer *lexer)
{
	char	*token;

	token = lexer->tokens[*i];
	if (ft_strcmp(token, "<") == 0)
	{
		(*current_cmd)->infile = create_io_file(lexer->tokens[++(*i)], \
		REDIRECT_INPUT);
		if (!(*current_cmd)->infile)
		{
			perror("Error: malloc for input redirection file");
			return (free_commands(*command_list), 0);
		}
	}
	else
	{
		(*current_cmd)->infile = create_io_file(lexer->tokens[++(*i)], \
		REDIRECT_HEREDOC);
		if (!(*current_cmd)->infile)
		{
			perror("Error: malloc for input redirection file");
			return (free_commands(*command_list), 0);
		}
	}
	return (1);
}
