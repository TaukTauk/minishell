/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:56:57 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 16:00:22 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_format	ft_parse_flag(char *str, t_format new)
{
	while (*str != '.' && !ft_strchr_pr(SPECIFIER, *str))
	{
		if (*str == '+')
			new.plus = 1;
		if (*str == '-')
			new.minus = 1;
		if (*str == ' ')
			new.space = 1;
		if (*str == '#')
			new.sharp = 1;
		str++;
	}
	return (new);
}

static t_format	ft_parse_width(char *str, va_list ptr, t_format new)
{
	int	specified;

	specified = 0;
	while (*str != '.' && !ft_strchr_pr(SPECIFIER, *str))
	{
		if (*str == '0' && ft_isdigit_pr(*(str - 1)) == 0)
			new.zero = 1;
		else if ((*str == '*' || (*str > '0' && *str <= '9')) && !specified)
		{
			if (*str == '*')
			{
				new.width = va_arg(ptr, int);
				if (new.width < 0)
				{
					new.minus = 1;
					new.width *= -1;
				}
			}
			else
				new.width = ft_atoi_pr(str);
			specified = 1;
		}
		str++;
	}
	return (new);
}

static t_format	ft_parse_precision(char *str, va_list ptr, t_format new)
{
	int	specified;

	specified = 0;
	while (!ft_strchr_pr(SPECIFIER, *str))
	{
		if ((*str == '*' || ft_isdigit_pr(*str)) && !specified)
		{
			if (*str == '*')
				new.precision = va_arg(ptr, int);
			else
				new.precision = ft_atoi_pr(str);
			specified = 1;
		}
		str++;
	}
	return (new);
}

int	ft_parse(char *str, va_list ptr)
{
	t_format	new;

	new = ft_parse_flag(str, ft_newformat());
	new = ft_parse_width(str, ptr, new);
	while (*str != '.' && !ft_strchr_pr(SPECIFIER, *str))
		str++;
	if (*str == '.' && !ft_strchr_pr(SPECIFIER, *str))
	{
		new.dot = 1;
		new = ft_parse_precision(str++, ptr, new);
		while (!ft_strchr_pr(SPECIFIER, *str) && *str)
			str++;
	}
	if (ft_strchr_pr(SPECIFIER, *str))
		new.specifier = *str;
	if (new.precision < 0)
		new.neg_prec = 1;
	return (ft_print_format(new, ptr));
}
