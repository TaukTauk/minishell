/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:39:00 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 13:30:24 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*cur;

	if (lst && *lst && del)
	{
		cur = (t_list *)*lst;
		while (cur)
		{
			tmp = cur->next;
			ft_lstdelone(cur, del);
			cur = tmp;
		}
		*lst = NULL;
	}
}
/*
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static int      nb_free_done;

void    ft_del(void *content)
{
        free(content);
        nb_free_done++;
}

t_list  *ft_lstnewone(void *content)
{
        t_list  *elem;

        elem = (t_list *)malloc(sizeof(t_list));
        if (!elem)
                return (NULL);
        if (!content)
                elem->content = NULL;
        else
                elem->content = content;
        elem->next = NULL;
        return (elem);
}

int main()
{
        t_list          *elem;
        t_list          *elem2;
        t_list          *elem3;
        t_list          *elem4;
        char            *str = strdup("hello");
        char            *str2 = strdup("world");
        char            *str3 = strdup("kernel");
        char            *str4 = strdup("operating");

        elem = ft_lstnewone(str);
        elem2 = ft_lstnewone(str2);
        elem3 = ft_lstnewone(str3);
        elem4 = ft_lstnewone(str4);
        if (!elem || !elem2 || !elem3 || !elem4)
                return (0);
        elem->next = elem2;
        elem2->next = elem3;
        elem3->next = elem4;
        ft_lstclear(&elem, &ft_del);
	if (elem == NULL)
		printf("Done\n");
        return (0);
}
*/
