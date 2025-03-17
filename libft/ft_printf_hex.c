/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:29:19 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 16:02:23 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_sharp(t_format new)
{
	if (new.specifier == 'X')
		return ("0X");
	return ("0x");
}

int	ft_printf_hex(t_format new, va_list ptr)
{
	int				count;
	unsigned int	n;
	int				len;

	count = 0;
	n = va_arg(ptr, unsigned int);
	len = ft_nbrlen(n) * (!(!n && !new.precision && new.dot));
	if (new.precision < 0 || new.precision < len || !new.dot)
		new.precision = len;
	new.width -= 2 * (new.sharp && n);
	if (!new.minus && new.width > new.precision \
	&& (!new.dot || new.neg_prec) && new.zero)
		count += ft_putnstr(ft_sharp(new), 2 * (new.sharp && new.zero && n)) + \
		ft_putnchar('0', new.width - new.precision);
	else if (!new.minus && new.width > new.precision)
		count += ft_putnchar(' ', new.width - new.precision) + \
		ft_putnstr(ft_sharp(new), 2 * (new.sharp && new.zero && n));
	count += ft_putnstr(ft_sharp(new), 2 * (new.sharp && !new.zero && n));
	count += ft_putnchar('0', new.precision - len);
	if (len)
		count += ft_recursive_hex(new, n, n);
	if (new.minus && new.width > new.precision)
		count += ft_putnchar(' ', new.width - new.precision);
	return (count);
}
