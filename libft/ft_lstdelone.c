/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:35:45 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 13:30:59 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del != NULL)
		(*del)(lst->content);
	free(lst);
}
/*
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void    ft_print_result(t_list *elem)
{
        write(1, elem->content, strlen(elem->content));
}

void    ft_del(void *content)
{
        free(content);
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
        alarm(5);
        if (!elem || !elem2 || !elem3 || !elem4)
                return (0);
        elem->next = elem2;
        elem2->next = elem3;
        elem3->next = elem4;
       	ft_lstdelone(elem3, &ft_del);
	while (elem != NULL)
	{
		printf("%s\n", (char *) elem->content);
		elem = elem->next;
	}
        return (0);
}
*/
