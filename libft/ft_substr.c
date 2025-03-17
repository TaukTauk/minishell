/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:48:36 by talin             #+#    #+#             */
/*   Updated: 2024/11/15 14:00:25 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	char	*tmp;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s == NULL || s_len < start)
		return (ft_strdup(""));
	if (start + len < s_len)
		ptr = (char *)malloc((len + 1) * sizeof(char));
	else
		ptr = (char *)malloc((s_len - start + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = start;
	tmp = ptr;
	while (i < (start + len) && s[i])
		*tmp++ = *(s + i++);
	*tmp = '\0';
	return (ptr);
}
/*
#include <stdio.h>

int	main()
{
	char	*ptr = ft_substr("hello world", 3, 5);
	printf("%s\n", ptr);
}
*/
