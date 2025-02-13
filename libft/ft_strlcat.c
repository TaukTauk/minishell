/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:19:27 by talin             #+#    #+#             */
/*   Updated: 2024/09/09 16:17:38 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	res;

	if (!dst || !src)
		return (0);
	i = 0;
	j = ft_strlen(dst);
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	if (size <= j)
		res = size + len;
	else
	{
		res = len + j;
		while (src[i] && (i + j) < size - 1)
		{
			dst[i + j] = src[i];
			i++;
		}
		dst[i + j] = '\0';
	}
	return (res);
}
/*
#include <string.h>
#include <stdio.h>

int	main()
{
	char	src[10] = "hello";
	char	dest[10] = "world";
	int	n = ft_strlcat(dest, src, 10);
	printf("n: %i, dest: %s\n", n , dest);
}
*/
