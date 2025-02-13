/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:45:53 by talin             #+#    #+#             */
/*   Updated: 2024/08/27 13:22:48 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char	src[6] = "hello";
	char	dest[8] = "cat";
	memmove(dest, src, 4);
	printf("%s\n", src);
}
*/
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char	str[100] = "Learningisfun";
	char	*dst;
	char	*src;
	dst = str;
	src = str;
	memmove(src + 8, dst, 10);
	printf("memmove overlap: %s\n", str);
}
*/
