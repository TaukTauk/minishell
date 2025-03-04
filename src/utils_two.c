/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:21:50 by talin             #+#    #+#             */
/*   Updated: 2025/03/04 11:22:10 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_multjoin(char **arr_str)
{
	char	*res;
	char	*tmp;

	if (!arr_str && !*arr_str)
		return (NULL);
	res = ft_strdup(*arr_str++);
	while (*arr_str)
	{
		tmp = ft_strjoin(res, *arr_str);
		free(res);
		res = tmp;
		arr_str++;
	}
	return (tmp);
}
