/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:30:50 by talin             #+#    #+#             */
/*   Updated: 2024/08/27 11:58:38 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (dest);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (n > 0)
	{
		*(d++) = *(s++);
		n--;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	const char	src[6] = "hello";
	char	dest[4] = "cat";
	memcpy(dest, src, 5);
	printf("%s\n", dest);
	return (0);
}
*/
