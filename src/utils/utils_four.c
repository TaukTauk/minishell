/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by talin             #+#    #+#             */
/*   Updated: 2025/03/21 13:57:28 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_of_dollar(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!str)
		return (count);
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

void	increasing_size(size_t *new_size, const char **ptr,
	int inside_double_quote, int inside_single_quote)
{
	if (!(**ptr == '\'' || **ptr == '\"'))
	{
		(*new_size)++;
		(*ptr)++;
	}
	else
	{
		if (((**ptr == '\'' && inside_double_quote) || \
		(**ptr == '\"' && inside_single_quote)))
		{
			(*new_size)++;
			(*ptr)++;
		}
		else
			(*ptr)++;
	}
}
