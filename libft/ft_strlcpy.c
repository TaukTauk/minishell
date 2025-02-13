/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:28 by talin             #+#    #+#             */
/*   Updated: 2024/09/09 16:17:13 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!src)
		return (0);
	i = ft_strlen(src);
	if (size == 0)
		return (i);
	if (i < size - 1)
		ft_memcpy(dst, src, i + 1);
	else if (size != 0)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (i);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int	main()
{
	char	src[10] = "hello";
	char	dest[10] = "AAAAA";
	size_t	n = ft_strlcpy(dest, src, 3);
	printf("n: %zu, dest: %s\n", n , dest);
}
*/
