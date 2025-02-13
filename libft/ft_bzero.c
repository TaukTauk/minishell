/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:12:20 by talin             #+#    #+#             */
/*   Updated: 2024/08/28 19:36:24 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	if (!n)
		return ;
	i = 0;
	str = s;
	while (i < n)
		*(str + i++) = '\0';
}
/*
#include <stdio.h>
#include <strings.h>
int	main()
{
	char	str[20] = "hello world";
	ft_bzero(str + 2, 5);
	printf("%s\n", str);
}
*/
