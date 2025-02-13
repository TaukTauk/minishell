/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:55:43 by talin             #+#    #+#             */
/*   Updated: 2024/08/29 17:36:16 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	if (!content)
	{
		ptr->content = NULL;
		ptr->next = NULL;
	}
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}
/*
#include <stdio.h>

int	main()
{
	t_list	*head;
	t_list	*ptr;

	head = ft_lstnew("hello");
	ptr = ft_lstnew("world");
	head->next = ptr;
	while (head != NULL)
	{
		printf("%s\n", (char *)head->content);
		head = head->next;
	}
}
*/
