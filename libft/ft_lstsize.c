/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:20:13 by talin             #+#    #+#             */
/*   Updated: 2024/08/29 17:44:06 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
#include <stdio.h>

int     main()
{
        t_list  *head;
        t_list  *ptr;
        t_list  *new;

        head = ft_lstnew("hello");
        ptr = ft_lstnew("world");
        new = ft_lstnew("kernel");
        head->next = ptr;
        ft_lstadd_front(&head, new);
	int	n = ft_lstsize(head);
	printf("n: %i\n", n);
}
*/
