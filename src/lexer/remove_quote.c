/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:39:10 by talin             #+#    #+#             */
/*   Updated: 2025/03/19 14:55:47 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	size_of_str_without_quote(char **str)
{
	int		size;
	char	quote_char;
	int		in_quote;
	int		i;

	size = 0;
	i = -1;
	in_quote = 0;
	quote_char = 0;
	while ((*str)[++i])
	{
		if (((*str)[i] == '"' || (*str)[i] == '\'') && !in_quote)
		{
			in_quote = 1;
			quote_char = (*str)[i];
		}
		else if ((*str)[i] == quote_char && in_quote)
		{
			in_quote = 0;
			quote_char = 0;
			size -= 2;
		}
		size++;
	}
	return (size);
}

static int	in_quote_or_not(char *str)
{
	int	in_quote;
	int	quote_char;
	int	i;

	i = -1;
	in_quote = 0;
	quote_char = 0;
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !in_quote)
		{
			in_quote = 1;
			quote_char = str[i];
		}
		else if (str[i] == quote_char && in_quote)
		{
			in_quote = 0;
			quote_char = 0;
		}
	}
	return (in_quote);
}

static void	copy_str_without_quote(char **clean_str, int in_quote,
				char quote_char, char **str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (in_quote_or_not(*str))
	{
		ft_strcpy(*clean_str, *str);
		return ;
	}
	while ((*str)[++i])
	{
		if (((*str)[i] == '"' || (*str)[i] == '\'') && !in_quote)
		{
			in_quote = 1;
			quote_char = (*str)[i];
		}
		else if ((*str)[i] == quote_char && in_quote)
		{
			in_quote = 0;
			quote_char = 0;
		}
		else
		{
			(*clean_str)[j] = (*str)[i];
			j++;
		}
	}
	(*clean_str)[j] = '\0';
}

void	remove_quote(char **str)
{
	char	*clean_str;
	int		size;
	char	quote_char;
	int		in_quote;

	size = size_of_str_without_quote(str);
	clean_str = (char *)malloc(sizeof(char) * (size + 1));
	if (!clean_str)
		return ;
	in_quote = 0;
	quote_char = 0;
	copy_str_without_quote(&clean_str, in_quote, quote_char, str);
	free(*str);
	*str = clean_str;
}
