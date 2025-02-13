/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:53:16 by talin             #+#    #+#             */
/*   Updated: 2024/09/09 16:02:16 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	ptr = ft_strdup(s);
	if (!ptr)
		return (NULL);
	while (ptr[i])
	{
		ptr[i] = (*f)(i, ptr[i]);
		i++;
	}
	return (ptr);
}
/*
#include <stdio.h>

char	ft_f(unsigned int i, char str)
{
	printf("index: %d, %c\n", i, str);
	return (str - 32);
}

int	main()
{
	char	str[10] = "hello";
	char	*ptr = ft_strmapi(str, ft_f);
	printf("result : %s\n", ptr);
	return 0;
}
*/
