/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:52:33 by talin             #+#    #+#             */
/*   Updated: 2024/08/28 14:33:15 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	chr;
	size_t			i;

	tmp = (unsigned char *)s;
	chr = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (tmp[i] == chr)
			return ((void *)(tmp + i));
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	const char	str[6] = "hello";
	char	*r;
	r = ft_memchr(str, 'l', 5);
	printf("str: %s\n", r);
}
*/
