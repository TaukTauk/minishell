/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:27:03 by talin             #+#    #+#             */
/*   Updated: 2025/03/19 13:15:49 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_io_file(t_redirection **file_list,
		char *file_name, int redirect_type, int order_num)
{
	t_redirection	*new_file;
	t_redirection	*last;

	if (!file_name)
		return (0);
	new_file = malloc(sizeof(t_redirection));
	if (!new_file)
		return (0);
	new_file->file_name = ft_strdup(file_name);
	if (!new_file->file_name)
		return (0);
	new_file->type = redirect_type;
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

int	ft_parse_in_red(t_command **command_list,
	t_command **current_cmd, t_lexer **current, t_data *data)
{
	if (!*current_cmd)
	{
		*command_list = create_command();
		if (!*command_list)
		{
			ft_putendl_fd
				("minishell: failed to allocate memory for command", 2);
			data->status = 2;
			return (free_commands(*command_list), 0);
		}
		*current_cmd = *command_list;
	}
	if (!ft_parse_in_red_two(command_list, current_cmd, current, data))
		return (0);
	return (1);
}

static int	parse_tokens_delimeter(t_command *command_list, t_data *data)
{
	t_command		*tmp;
	t_redirection	*file;

	tmp = command_list;
	while (tmp)
	{
		if (tmp->redirections)
		{
			file = tmp->redirections;
			while (file)
			{
				if (file->type == REDIRECT_HEREDOC)
				{
					if (!delimeter_read(file, tmp, data))
						return (0);
				}
				file = file->next;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

t_command	*parse_tokens(t_lexer *lexer, t_data *data)
{
	t_command	*command_list;
	t_command	*current_cmd;
	t_lexer		*current;

	if (!lexer)
		return (NULL);
	command_list = NULL;
	current_cmd = NULL;
	current = lexer;
	while (current)
	{
		if (!parse_tokens_statement(&command_list,
				&current_cmd, &current, data))
			return (free_lexer(lexer), NULL);
		current = current->next;
	}
	if (!parse_tokens_delimeter(command_list, data))
	{
		free_lexer(lexer);
		return (free_commands(command_list), NULL);
	}
	return (free_lexer(lexer), command_list);
}

// void	print_commands(t_command *cmd)
// {
// 	int				i;
// 	t_redirection	*tmp;

// 	while (cmd)
// 	{
// 		printf("Command: %s\n", cmd->cmd);
// 		if (cmd->args)
// 		{
// 			printf("Arguments:\n");
// 			i = -1;
// 			while (cmd->args[++i])
// 				printf("  %s\n", cmd->args[i]);
// 		}
// 		if (cmd->redirections)
// 		{
// 			tmp = cmd->redirections;
// 			while (tmp)
// 			{
// 				if (tmp->type == REDIRECT_INPUT)
// 					printf("Input file:");
// 				else if (tmp->type == REDIRECT_OUTPUT)
// 					printf("Output file:");
// 				else if (tmp->type == REDIRECT_HEREDOC)
// 					printf("Heredoc:");
// 				else if (tmp->type == REDIRECT_APPEND)
// 					printf("Output file append:");
// 				printf(" %s (Type: %d), order number ==> %d\n", \
// 				tmp->file_name, tmp->type, tmp->order_value);
// 				if (tmp->content)
// 					printf("%s", tmp->content);
// 				tmp = tmp->next;
// 			}
// 		}
// 		printf("Input order : %d\n", cmd->input_order);
// 		printf("Output order : %d\n", cmd->output_order);
// 		cmd = cmd->next;
// 		printf("\n");
// 	}
// }
