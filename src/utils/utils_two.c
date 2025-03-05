/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:21:50 by talin             #+#    #+#             */
/*   Updated: 2025/03/05 13:54:24 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	ft_is_only_space(char *input)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			size++;
		i++;
	}
	if (size == (int)ft_strlen(input))
		return (1);
	return (0);
}
