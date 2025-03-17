/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:07:27 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 16:01:56 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_char(t_format new, va_list ptr)
{
	int		count;
	char	c;

	count = 0;
	if (new.specifier == 'c')
		c = va_arg(ptr, int);
	else
		return (ft_putnchar('%', 1));
	new.precision = 1;
	if (!new.minus && new.zero)
		count += ft_putnchar('0', new.width - new.precision);
	else if (!new.minus && new.width > new.precision)
		count += ft_putnchar(' ', new.width - new.precision);
	count += ft_putnchar(c, 1);
	if (new.minus && new.width - new.precision > 0)
		count += ft_putnchar(' ', new.width - new.precision);
	return (count);
}

int	ft_printf_str(t_format new, va_list ptr)
{
	int		count;
	char	*str;

	str = va_arg(ptr, char *);
	count = 0;
	if (!str && new.dot && new.precision < ft_strlen_pr("(null)"))
		return (ft_putnchar(' ', new.width));
	if (!str)
		str = (char *)"(null)";
	if (new.precision > ft_strlen_pr(str) || new.precision < 0 || !new.dot)
		new.precision = ft_strlen_pr(str);
	if (!new.minus && new.width > new.precision \
	&& new.zero && (!new.dot || new.neg_prec))
		count += ft_putnchar('0', new.width - new.precision);
	else if (!new.minus && new.width - new.precision > 0)
		count += ft_putnchar(' ', new.width - new.precision);
	count += ft_putnstr(str, new.precision);
	if (new.minus && new.width - new.precision > 0)
		count += ft_putnchar(' ', new.width - new.precision);
	return (count);
}
