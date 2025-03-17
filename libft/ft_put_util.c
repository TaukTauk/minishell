/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:14:54 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 16:07:26 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnchar(int c, int size)
{
	int	i;

	i = 0;
	if (size <= 0)
		return (0);
	while (i < size)
	{
		write(1, &c, 1);
		i++;
	}
	return (i);
}

int	ft_putnstr(char *str, int size)
{
	int	i;

	i = 0;
	if (size <= 0)
		return (0);
	while (i < size)
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

char	ft_sign(t_format new, int neg)
{
	if (neg)
		return ('-');
	else if (new.plus && !neg)
		return ('+');
	else
		return (' ');
}
