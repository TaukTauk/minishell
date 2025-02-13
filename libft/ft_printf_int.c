/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:30:24 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 16:04:30 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_size(int n)
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

static char	*ft_itoa_pr(int n)
{
	char		*ptr;
	size_t		size;
	long int	num;

	num = (long int)n;
	size = ft_size(n);
	if (n < 0)
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

int	ft_printf_nbr(t_format new, char *nbr, int len, int neg)
{
	int	count;

	count = 0;
	new.width -= (new.space && !neg && !new.plus && new.width);
	if (neg || new.plus)
		count += ft_putnchar(ft_sign(new, neg), new.zero \
		&& (!new.dot || new.neg_prec));
	else if (new.space)
		count += ft_putnchar(' ', new.zero && !new.dot);
	if (!new.minus && new.width > new.precision && \
	(!new.dot || new.neg_prec) && new.zero)
		count += ft_putnchar('0', new.width - new.precision - neg - new.plus);
	else if (!new.minus && new.width > new.precision)
		count += ft_putnchar(' ', new.width - new.precision - neg - new.plus);
	if (neg || new.plus)
		count += ft_putnchar(ft_sign(new, neg), \
		!new.zero || (new.dot && !new.neg_prec));
	else if (new.space)
		count += ft_putnchar(' ', !new.zero || new.dot);
	count += ft_putnchar('0', (new.precision - len));
	count += ft_putnstr(nbr, len);
	if (new.minus && new.width > new.precision)
		count += ft_putnchar(' ', new.width - new.precision - neg - new.plus);
	return (count);
}

int	ft_printf_int(t_format new, va_list ptr)
{
	int		count;
	int		n;
	char	*nbr;
	int		len;
	int		neg;

	count = 0;
	n = va_arg(ptr, int);
	neg = (n < 0);
	nbr = ft_itoa_pr(n);
	if (neg)
		new.plus = 0;
	len = ft_strlen_pr(nbr);
	if (*nbr == '0' && !new.precision && new.dot)
		len = 0;
	if (new.precision < len || !new.dot)
		new.precision = len;
	count += ft_printf_nbr(new, nbr, len, neg);
	free(nbr);
	return (count);
}
