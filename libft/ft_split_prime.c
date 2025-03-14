/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_prime.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:47:56 by juhtoo-h          #+#    #+#             */
/*   Updated: 2025/03/14 13:49:51 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char str)
{
	if ((str >= 9 && str <= 13) || str == 32)
		return (1);
	return (0);
}

static size_t	ft_substr_count(char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (*s == 0)
		return (0);
	while (s[i] != '\0' && i < ft_strlen(s))
	{
		if (!ft_isspace(s[i]) && (ft_isspace(s[i + 1])
				|| s[i + 1] == '\0' || s[i + 1] == '\n'))
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_substr_len(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && !ft_isspace(s[i]) && s[i] != '\n')
		i++;
	return (i);
}

static char	**ft_free(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free(str);
	return (NULL);
}

char	**ft_split_prime(char *s)
{
	char	**str;
	size_t	i;
	size_t	j;

	str = (char **) malloc((ft_substr_count(s) + 1) * sizeof(char *));
	if (!s || !str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0' && i < ft_strlen(s) && s[i] != '\n')
	{
		if (!ft_isspace(s[i]))
		{
			str[j] = ft_substr(s, i, ft_substr_len(&s[i]));
			if (!str[j])
				return (ft_free(str, j));
			j++;
			i += ft_substr_len(&s[i]);
		}
		else
			i++;
	}
	str[j] = 0;
	return (str);
}
