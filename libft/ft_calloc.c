/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:50:29 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 13:20:28 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	req;

	req = (size_t)(nmemb * size);
	if ((long) nmemb == 0 || (long) size == 0)
		req = 1;
	else if ((long) nmemb < 0 || (long) size < 0)
		return (NULL);
	ptr = malloc(req);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, req);
	return (ptr);
}
/*
#include <stdio.h>
int	main()
{
	int	n = -5;
	int	*array;

	array = (int *)ft_calloc(n, sizeof(int));
	if (array == NULL)
	{
		return (0);
	}
	for (int i = 0; i < n; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
	free(array);
	return (0);
}
*/
