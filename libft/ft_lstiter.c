/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:45:07 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 13:31:55 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;

	if (!lst || !f)
		return ;
	ptr = lst;
	while (ptr)
	{
		(*f)(ptr->content);
		ptr = ptr->next;
	}
}
/*
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void    ft_modify_list_with_d(void *elem)
{
        int             len;
        char            *content;

        len = 0;
        content = (char *)elem;
        while (content[len])
        {
		if (content[len] >= 'a' && content[len] <= 'z')
			content[len] -= 32;
                len++;
        }
}

void    ft_print_result(t_list *elem)
{
        int             len;

        while (elem)
        {
                len = 0;
                while (((char *)elem->content)[len])
                        len++;
                write(1, elem->content, len);
                write(1, "\n", 1);
                elem = elem->next;
        }
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
        ft_lstiter(elem, &ft_modify_list_with_d);
        ft_print_result(elem);
        return (0);
}
*/
