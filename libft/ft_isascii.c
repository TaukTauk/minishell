/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:00:39 by talin             #+#    #+#             */
/*   Updated: 2024/08/27 13:51:06 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main()
{
	int	n = ft_isascii(0);
	int	x = ft_isascii(-1);
	int	y = ft_isascii(128);
	int	z = ft_isascii(127);
	printf("n: %d, x: %d, y: %d, z: %d\n", n, x, y, z);
}
*/
