/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:40:15 by talin             #+#    #+#             */
/*   Updated: 2025/03/04 12:50:23 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strnlen(const char *s, size_t max_len)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (len < max_len && s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;

	if (s == NULL)
		return (NULL);
	len = ft_strnlen(s, n);
	dup = (char *)malloc((sizeof(char) * len) + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

size_t	ft_strcspn(const char *str, const char *reject)
{
	size_t		i;
	const char	*r;

	if (str == NULL || reject == NULL)
	{
		perror("Error:");
		return (0);
	}
	i = 0;
	while (str[i])
	{
		r = reject;
		while (*r != '\0')
		{
			if (str[i] == *r)
			{
				return (i);
			}
			r++;
		}
		i++;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (0 - ((unsigned char)s2[i]));
	if (!s2)
		return ((unsigned char)s1[i]);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
