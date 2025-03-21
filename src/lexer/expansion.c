/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:54:59 by talin             #+#    #+#             */
/*   Updated: 2025/03/21 16:52:25 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	insert_node(t_lexer **prev, t_lexer **temp,
			t_lexer **lexer, t_lexer **new_start)
{
	if (*prev)
		(*prev)->next = (*temp);
	else
		(*lexer) = (*temp);
	(*new_start) = (*temp);
}

static void	command_split(t_lexer **current, t_lexer **prev,
			t_lexer **lexer, char **token)
{
	int		i;
	t_lexer	*temp;
	t_lexer	*new_start;
	t_lexer	*last_new;
	t_lexer	*next_node;

	next_node = (*current)->next;
	i = -1;
	while (token[++i])
	{
		temp = new_lexer_node(TKN_WORD, token[i]);
		if (i == 0)
			insert_node(prev, &temp, lexer, &new_start);
		else
			if (last_new)
				last_new->next = temp;
		last_new = temp;
	}
	if (last_new)
		last_new->next = next_node;
	free((*current)->value);
	free(*current);
	*current = new_start;
	free(token);
}

static int	splitter(t_lexer **current, t_lexer **prev,
	t_lexer **lexer, int status)
{
	char	**token;

	if (status == 1 && empty_or_not((*current)->value))
	{
		token = ft_split_prime((*current)->value);
		if (!token)
			return (0);
		command_split(current, prev, lexer, token);
	}
	return (1);
}

static int	expansion_utils(t_lexer **current,
	t_lexer **prev, t_lexer **lexer, t_data *data)
{
	int	status;

	while (*current)
	{
		status = 0;
		if ((*prev) && (*prev)->token_type == TKN_RDHEREDOC)
		{
			(*prev) = (*current);
			(*current) = (*current)->next;
			continue ;
		}
		if (!expand_var(&((*current)->value), data, current, &status))
			return (free_lexer(*lexer), 0);
		if (splitter(current, prev, lexer, status) == 0)
			return (0);
		else
		{
			(*prev) = (*current);
			(*current) = (*current)->next;
		}
	}
	*current = *lexer;
	return (1);
}

int	parameter_expansion(t_lexer **lexer, t_data *data)
{
	t_lexer	*current;
	t_lexer	*prev;

	if (!lexer)
		return (0);
	current = *lexer;
	prev = NULL;
	if (expansion_utils(&current, &prev, lexer, data) == 0)
		return (0);
	prev = NULL;
	while (current)
	{
		current->expand = 0;
		if (prev)
		{
			if (prev->token_type == TKN_RDHEREDOC && \
				single_quote_token(current->value))
				current->expand = 1;
		}
		prev = current;
		current = current->next;
	}
	return (1);
}
