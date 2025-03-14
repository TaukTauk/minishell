/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:50:51 by talin             #+#    #+#             */
/*   Updated: 2025/03/14 11:45:17 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer	*new_lexer_node(int token_type, char *value)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->token_type = token_type;
	node->value = value;
	node->error = 0;
	node->next = NULL;
	return (node);
}

void	add_token(t_lexer **lexer, int token_type, char *value)
{
	t_lexer	*new_node;
	t_lexer	*current;

	new_node = new_lexer_node(token_type, value);
	if (!new_node)
	{
		ft_putendl_fd("minishell: malloc error for adding token", 2);
		return ;
	}
	if (!*lexer)
	{
		*lexer = new_node;
		return ;
	}
	current = *lexer;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

int	get_token_type(char *token)
{
	if (!ft_strcmp(token, "<"))
		return (TKN_IN);
	else if (!ft_strcmp(token, ">"))
		return (TKN_OUT);
	else if (!ft_strcmp(token, ">>"))
		return (TKN_RDAPPEND);
	else if (!ft_strcmp(token, "<<"))
		return (TKN_RDHEREDOC);
	else if (!ft_strcmp(token, "|"))
		return (TKN_PIPE);
	else
		return (TKN_WORD);
}

// void	free_lexer(t_lexer *lexer)
// {
// 	t_lexer	*temp;

// 	while (lexer)
// 	{
// 		temp = lexer;
// 		lexer = lexer->next;
// 		if (temp->value)
// 			free(temp->value);
// 		free(temp);
// 	}
// }

t_lexer	*tokenize(char *input, t_data *data)
{
	t_lexer	*lexer;

	if (!input)
		return (NULL);
	lexer = NULL;
	if (!ft_tokenize_four(&lexer, input, data))
		return (NULL);
	return (lexer);
}
