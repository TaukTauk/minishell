/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:40:15 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 20:51:25 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_size(unsigned int n)
{
	size_t		i;
	long int	num;

	num = (long int)n;
	i = 0;
	if (num < 0)
	{
		num *= -1;
	}
	while (num > 9)
	{
		num /= 10;
		i++;
	}
	if (num < 10)
		i++;
	return (i);
}

static char	*ft_uitoa(unsigned int n)
{
	char		*ptr;
	size_t		size;
	long int	num;

	num = (long int)n;
	size = ft_size(n);
	if ((int)n < 0)
		num *= -1;
	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	*(ptr + size) = 0;
	while (size--)
	{
		*(ptr + size) = num % 10 + '0';
		num /= 10;
	}
	return (ptr);
}

static int	ft_printf_nbr(t_format new, char *nbr, int len)
{
	int	count;

	count = 0;
	new.plus = 0;
	if (new.space)
		count += ft_putnchar(' ', new.zero && !new.dot);
	if (!new.minus && new.width > new.precision && \
	(!new.dot || new.neg_prec) && new.zero)
		count += ft_putnchar('0', new.width - new.precision);
	else if (!new.minus && new.width > new.precision)
		count += ft_putnchar(' ', new.width - new.precision);
	else if (new.space)
		count += ft_putnchar(' ', !new.zero || new.dot);
	count += ft_putnchar('0', (new.precision - len));
	count += ft_putnstr(nbr, len);
	if (new.minus && new.width > new.precision)
		count += ft_putnchar(' ', new.width - new.precision);
	return (count);
}

int	ft_printf_uint(t_format new, va_list ptr)
{
	int				count;
	unsigned int	n;
	char			*nbr;
	int				len;
	int				neg;

	count = 0;
	n = va_arg(ptr, unsigned int);
	neg = ((int)n < 0);
	nbr = ft_uitoa(n);
	if (neg)
		new.plus = 0;
	len = ft_strlen_pr(nbr);
	if (*nbr == '0' && !new.precision && new.dot)
		len = 0;
	if (new.precision < len || !new.dot)
		new.precision = len;
	count += ft_printf_nbr(new, nbr, len);
	free(nbr);
	return (count);
}
