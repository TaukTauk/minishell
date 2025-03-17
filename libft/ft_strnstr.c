/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:57:28 by talin             #+#    #+#             */
/*   Updated: 2024/09/09 16:04:04 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	size;

	if (!big)
		return (NULL);
	i = 0;
	size = ft_strlen(little);
	if (!big && !little)
		return (0);
	if (size == 0 || big == little)
		return ((char *)(big));
	while (i < len && big[i])
	{
		j = 0;
		while (little[j] && big[i + j] && \
				i + j < len && little[j] == big[i + j])
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	const char	big[12] = "Foo Bar Baz";
	const char	little[5] = "Bar";
	char	*ptr = ft_strnstr(big, little, 7);
	printf("ptr: %s\n", ptr);
}
*/
