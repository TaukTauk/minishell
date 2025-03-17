/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:26:08 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 16:11:37 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_pr(char *s, int c)
{
	int		i;
	char	chr;

	if (!s)
		return (0);
	chr = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == chr)
			return ((s + i));
		i++;
	}
	if (s[i] == chr)
		return ((s + i));
	return (0);
}

int	ft_strlen_pr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit_pr(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	return (0);
}

static int	ft_isspace_pr(const char str)
{
	if ((str >= 9 && str <= 13) || str == 32)
		return (1);
	return (0);
}

int	ft_atoi_pr(char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (0);
	while (ft_isspace_pr(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
