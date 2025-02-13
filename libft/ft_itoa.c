/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:01:30 by talin             #+#    #+#             */
/*   Updated: 2024/08/28 19:18:04 by talin            ###   ########.fr       */
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
		i++;
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

char	*ft_itoa(int n)
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
	if (n < 0)
		*(ptr + 0) = '-';
	return (ptr);
}
/*
#include <stdio.h>

int	main()
{
	int	x = -2147483648;
	size_t	n = ft_size(x);
	char	*ptr = ft_itoa(x);
	printf("n: %zu, ptr: %s\n", n, ptr);
}
*/
