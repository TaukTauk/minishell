/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:21:50 by talin             #+#    #+#             */
/*   Updated: 2025/03/17 13:23:34 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_multjoin(char **arr_str)
{
	char	*res;
	char	*tmp;

	if (!arr_str && !*arr_str)
		return (NULL);
	res = ft_strdup(*arr_str++);
	while (*arr_str)
	{
		tmp = ft_strjoin(res, *arr_str);
		if (!tmp)
		{
			free(res);
			return (NULL);
		}
		free(res);
		res = tmp;
		arr_str++;
	}
	tmp = NULL;
	free(tmp);
	return (res);
}

int	ft_is_only_space(char *input)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			size++;
		i++;
	}
	if (size == (int)ft_strlen(input))
		return (1);
	return (0);
}

int	get_token_count(t_lexer *lexer)
{
	int		count;
	t_lexer	*current;

	count = 0;
	current = lexer;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_lexer	*get_token_at_index(t_lexer *lexer, int index)
{
	t_lexer	*current;
	int		i;

	i = 0;
	current = lexer;
	while (current && i < index)
	{
		current = current->next;
		i++;
	}
	return (current);
}
