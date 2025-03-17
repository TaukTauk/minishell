/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:22:36 by talin             #+#    #+#             */
/*   Updated: 2024/08/29 16:55:52 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}
/*
#include <stdio.h>

int	main()
{
	t_list	*head;
	t_list	*ptr;
	t_list	*res;

	if (!(head = (t_list *)malloc(sizeof(t_list))))
		return (0);
	head->content = "hello";
	head->next = NULL;
	if (!(ptr = (t_list *)malloc(sizeof(t_list))))
		return (0);
	ptr->content = "world";
	ptr->next = NULL;
	head->next = ptr;
	res = ft_lstlast(head);
	printf("%s\n", (char *)res->content);
}
*/
