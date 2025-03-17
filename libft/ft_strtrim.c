/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:21:16 by talin             #+#    #+#             */
/*   Updated: 2024/09/09 15:50:44 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char const s1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*ptr;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	i = 0;
	start = 0;
	while (s1[start] && ft_check(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_check(s1[end - 1], set))
		end--;
	ptr = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!ptr)
		return (NULL);
	while (start < end)
		ptr[i++] = s1[start++];
	ptr[i] = '\0';
	return (ptr);
}
/*
#include <stdio.h>

int	main()
{
	char	s1[] = "lorem \n ipsum \t dolor \n sit \t amet";
	char	*s2 = ft_strtrim(s1, " ");
	printf("s2:%s\n", s2);
}
*/
