/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:38:24 by talin             #+#    #+#             */
/*   Updated: 2024/09/09 15:50:16 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		n;
	char	chr;

	if (!s)
		return (NULL);
	n = ft_strlen((char *)s);
	chr = (char)c;
	while (n > 0)
	{
		if (s[n] == chr)
			return ((char *)(s + n));
		n--;
	}
	if (s[n] == chr)
		return ((char *)(s + n));
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	char	str[] = "pepe y cparlos";
	printf("str: %s\n", ft_strrchr(str, 'c'));
}
*/
