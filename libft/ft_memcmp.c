/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:50:52 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 13:35:06 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*d1;
	unsigned char	*d2;
	size_t			i;

	i = 0;
	if (n == 0)
		return (0);
	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	while (i < n)
	{
		if ((unsigned char)d1[i] != (unsigned char)d2[i])
			return ((unsigned char)d1[i] - (unsigned char)d2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	int	n = ft_memcmp("hello1", "hello2", 6);
	printf("n: %i\n", n);
}
*/
