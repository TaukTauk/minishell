/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:48:19 by talin             #+#    #+#             */
/*   Updated: 2024/08/29 19:04:40 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*ptr_lst;

	if (!f || !del || !lst)
		return (NULL);
	ptr_lst = NULL;
	while (lst)
	{
		ptr = ft_lstnew(f(lst->content));
		if (!ptr)
		{
			ft_lstclear(&ptr_lst, (*del));
			return (NULL);
		}
		ft_lstadd_back(&ptr_lst, ptr);
		lst = lst->next;
	}
	return (ptr_lst);
}
/*
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void    ft_print_result(t_list *elem)
{
        int             len;

        len = 0;
        while (((char *)elem->content)[len])
                len++;
        write(1, ((char *)elem->content), len);
        write(1, "\n", 1);
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

void    *ft_map(void *ct)
{
        int i;
        void    *c;
        char    *pouet;

        c = ct;
        i = -1;
        pouet = (char *)c;
        while (pouet[++i])
                if (pouet[i] >= 'a' && pouet[i] <= 'z')
                        pouet[i] -= 32;
        return (c);
}

void    ft_del(void *content)
{
        free(content);
}

int main(int argc, const char *argv[])
{
        t_list          *elem;
        t_list          *elem2;
        t_list          *elem3;
        t_list          *elem4;
        t_list          *list;
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
        if (!(list = ft_lstmap(elem, &ft_map, &ft_del)))
        	return (0);
        if (list == elem)
                write(1, "A new list is not returned\n", 27);
        ft_print_result(list);
        while (list->next)
        {
                list = list->next;
                ft_print_result(list);
        }
        return (0);
}
*/
