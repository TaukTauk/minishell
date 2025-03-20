/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_two.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:52:57 by rick              #+#    #+#             */
/*   Updated: 2025/03/20 15:34:45 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigint_delim(int sig)
{
	(void)sig;
	g_delim_interrupt = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

int	delimeter_lines(t_redirection *delimeter, t_data *data)
{
	char	*line;

	(void)data;
	while (1)
	{
		signal(SIGINT, handle_sigint_delim);
		if (g_delim_interrupt)
		{
			data->status = 130;
			g_delim_interrupt = 0;
			return (0);
		}
		line = readline("> ");
		if (!line)
		{
			error_delimeter(delimeter->file_name);
			write(1, "\n", 1);
			return (1);
		}
		if (ft_strcmp(line, delimeter->file_name) == 0)
			return (free(line), 1);
		if (!delimeter_append(delimeter, line))
			return (free(line), 0);
		free(line);
	}
}

int	delimeter_expand(t_redirection *delimeter, t_data *data)
{
	char	*expand;
	char	*temp;

	if (!delimeter || !delimeter->content)
		return (0);
	expand = quote_expand(delimeter->content, data);
	if (expand)
	{
		free(delimeter->content);
		temp = ft_strjoin(expand, "\n");
		free(expand);
		delimeter->content = temp;
		return (1);
	}
	else
		ft_error("delimeter: failed to expand delimeter");
	return (0);
}

int	delimeter_read(t_redirection *delimeter, t_command *command, t_data *data)
{
	char	*temp;

	if (!delimeter || !command || !command->redirections)
		return (0);
	if (!delimeter_content(delimeter))
		return (0);
	if (!delimeter_lines(delimeter, data))
	{
		free(delimeter->content);
		delimeter->content = NULL;
		return (0);
	}
	if (delimeter->expand == 0)
	{
		if (!delimeter_expand(delimeter, data))
			return (0);
	}
	else
	{
		temp = ft_strjoin(delimeter->content, "\n");
		free(delimeter->content);
		delimeter->content = temp;
	}
	return (1);
}
