/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:54:59 by talin             #+#    #+#             */
/*   Updated: 2025/03/14 22:46:22 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	expand_variable_copy(char **ptr, t_data *data, char **output_ptr)
// {
// 	int	inside_single_quote;
// 	int	inside_double_quote;

// 	inside_single_quote = 0;
// 	inside_double_quote = 0;
// 	while (*ptr && **ptr != '\0')
// 	{
// 		if (**ptr == '\'' || **ptr == '\"')
// 			ft_quote_handle(ptr, &inside_single_quote, &inside_double_quote);
// 		if (**ptr == '$' && !inside_single_quote)
// 		{
// 			get_value(ptr, data, output_ptr);
// 			if (!*ptr || !**ptr)
// 				break ;
// 			continue ;
// 		}
// 		if (**ptr)
// 			*(*output_ptr)++ = *(*ptr)++;
// 	}
// 	*(*output_ptr) = '\0';
// }

// char	*expand_variable(char *input, t_data *data)
// {
// 	char	*expanded_str;
// 	char	*ptr;
// 	char	*output_ptr;
// 	int		size;

// 	if (!input)
// 		return (NULL);
// 	size = calculate_expanded_size(input, data);
// 	if (size == -1)
// 		return (NULL);
// 	expanded_str = malloc(size + 1);
// 	if (!expanded_str)
// 		return (perror("malloc"), NULL);
// 	ptr = input;
// 	output_ptr = expanded_str;
// 	expand_variable_copy(&ptr, data, &output_ptr);
// 	return (expanded_str);
// }

// int	ft_contain_dollar_sign(char *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '$')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_is_empty(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!ft_isspace(str[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	expand_var(char **cmd, t_data *data, int index)
// {
// 	char	*expanded_cmd;

// 	expanded_cmd = expand_variable(*cmd, data);
// 	if (ft_contain_dollar_sign(*cmd) && ft_is_empty(expanded_cmd))
// 	{
// 		data->empty_list[data->index] = index;
// 		data->index++;
// 		data->empty_list[data->index] = -1;
// 	}
// 	if (expanded_cmd)
// 	{
// 		free(*cmd);
// 		*cmd = expanded_cmd;
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

// int	parameter_expansion(t_lexer *tokens, t_data *data)
// {
// 	int		i;

// 	i = -1;
// 	if (!tokens)
// 		return (0);
// 	data->empty_list = (int *)malloc(sizeof(int) * (tokens->token_count + 1));
// 	if (!data->empty_list)
// 		return (0);
// 	data->index = 0;
// 	data->empty_list[0] = -1;
// 	while (tokens->tokens[++i])
// 	{
// 		if (i >= 1 && ft_strcmp(tokens->tokens[i - 1], "<<") == 0)
// 			continue ;
// 		if (!expand_var(&(tokens->tokens[i]), data, i))
// 			return (0);
// 	}
// 	i = -1;
// 	while (tokens->tokens[++i])
// 		remove_quote(&(tokens->tokens[i]));
// 	return (1);
// }

int ft_contain_dollar_sign(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

int ft_is_empty(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isspace(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int expand_var(char **cmd, t_data *data, t_lexer **lexer, int *status)
{
    char *expanded_cmd;

    expanded_cmd = expand_variable(*cmd, data);
	if (strcmp(expanded_cmd, *cmd) != 0 && !ft_strchr(expanded_cmd, '\"')
		&& !ft_strchr(expanded_cmd, '\''))
		*status = 1;
    if (ft_contain_dollar_sign(*cmd) && ft_is_empty(expanded_cmd))
	    (*lexer)->error = 1;
    if (expanded_cmd)
    {
        free(*cmd);
        *cmd = expanded_cmd;
        return (1);
    }
    else
        return (0);
}

int	empty_or_not(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (!ft_isspace(token[i]))
			return (1);
		i++;
	}
	return (0);
}

void command_split(t_lexer **current, t_lexer **prev, t_lexer **lexer)
{
	int     i;
	char    **token;
	t_lexer	*temp;
	t_lexer	*new_start;
	t_lexer	*last_new;
	t_lexer	*next_node;

	token = ft_split_prime((*current)->value);
	if (!token)
		return ;
	next_node = (*current)->next;
	i = -1;
	while (token[++i])
	{
		temp = new_lexer_node(TKN_WORD, token[i]);
		if (i == 0)
		{
			if (*prev)
				(*prev)->next = temp;
			else
				*lexer = temp;
			new_start = temp;
		}
		else
		{
			if (last_new)
				last_new->next = temp;
		}
		last_new = temp;
	}
	if (last_new)
		last_new->next = next_node;
	free((*current)->value);
	free(*current);
	*current = new_start;
	free(token);
}

// void	command_split(t_lexer **current, t_lexer **prev)
// {
// 	int		i;
// 	char	**token;
// 	t_lexer	*temp;
// 	t_lexer	*tempp;

// 	token = ft_split_prime((*current)->value);
// 	tempp = (*prev);
// 	i = -1;
// 	while (token[++i])
// 	{
// 		temp = new_lexer_node(TKN_WORD, token[i]);
// 		if (!tempp)
// 		{
// 			free((*current)->value);
// 			(*current)->value = token[i];
// 			tempp = (*current);
// 		}
// 		else
// 		{
// 			tempp->next = temp;
// 			tempp = tempp->next;
// 		}
// 	}
// 	tempp = (*current)->next;
// }

int parameter_expansion(t_lexer **lexer, t_data *data)
{
    t_lexer *current;
    t_lexer *prev;
	int		status;

    if (!lexer)
        return (0);
    current = *lexer;
    prev = NULL;
    while (current)
    {
		status = 0;
        if (prev && prev->token_type == TKN_RDHEREDOC)
        {
            prev = current;
            current = current->next;
            continue ;
        }
        if (!expand_var(&(current->value), data, &current, &status))
            return (free_lexer(*lexer), 0);
		if (status && empty_or_not(current->value))
			command_split(&current, &prev, lexer);
		else
		{
        	prev = current;
        	current = current->next;
		}
    }
    current = *lexer;
    while (current)
    {
        remove_quote(&(current->value));
        current = current->next;
    }
    return (1);
}
