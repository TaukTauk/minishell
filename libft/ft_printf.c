/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:54:26 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 16:07:04 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_loop(const char *str)
{
	char	*first;

	first = (char *)str++;
	while (*str && !ft_strchr_pr(SPECIFIER, *str))
		str++;
	if (!(*str))
		str = first;
	return ((char *)(str));
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	int		count;

	count = 0;
	va_start(ptr, str);
	while (*str)
	{
		if (*str == '%')
		{
			if (!*(++str))
			{
				va_end(ptr);
				return (-1);
			}
			if (*(str))
				count += ft_parse((char *)str, ptr);
			str = ft_loop(str - 1);
		}
		else
			count += ft_putchar_pr(*str);
		if (*str)
			str++;
	}
	va_end(ptr);
	return (count);
}

t_format	ft_newformat(void)
{
	t_format	new;

	new.plus = 0;
	new.minus = 0;
	new.space = 0;
	new.zero = 0;
	new.dot = 0;
	new.width = 0;
	new.precision = 0;
	new.neg_prec = 0;
	new.sharp = 0;
	new.specifier = 0;
	return (new);
}

int	ft_print_format(t_format new, va_list ptr)
{
	int	count;

	count = 0;
	if (new.specifier == 'c' || new.specifier == '%')
		count = ft_printf_char(new, ptr);
	if (new.specifier == 's')
		count = ft_printf_str(new, ptr);
	if (new.specifier == 'i' || new.specifier == 'd')
		count = ft_printf_int(new, ptr);
	if (new.specifier == 'u')
		count = ft_printf_uint(new, ptr);
	if (new.specifier == 'x' || new.specifier == 'X')
		count = ft_printf_hex(new, ptr);
	if (new.specifier == 'p')
		count = ft_printf_ptr(new, ptr);
	if (new.specifier == 0)
		count += ft_putnchar('%', 1);
	return (count);
}

int	ft_putchar_pr(char c)
{
	write(1, &c, 1);
	return (1);
}
