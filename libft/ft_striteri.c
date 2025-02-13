/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:47:49 by talin             #+#    #+#             */
/*   Updated: 2024/08/26 16:01:58 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f || !(*s))
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>

void	ft_f(unsigned int i, char *str)
{
	char	*ptr;
	unsigned int	j;

	ptr = str;
	j = 0;
	while (ptr[j])
	{
		if (ptr[j] >= 'a' && ptr[j] <= 'z')
			ptr[j] -= 32;
		j++;
	}
	printf("index: %d, %s\n", i, str);
}

int	main()
{
	char	str[10] = "hello";
	ft_striteri(str, ft_f);
	printf("str: %s\n", str);
	return (0);
}
*/
