/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:55:49 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 16:08:56 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*next_line(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = (char *)malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*new_line(char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(buffer);
	return (str);
}

char	*read_line(int fd, char *buffer)
{
	char	*ptr;
	ssize_t	n;

	ptr = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!ptr)
		return (NULL);
	n = 1;
	while (!ft_strchr_gnl(buffer, '\n') && n > 0)
	{
		n = read(fd, ptr, BUFFER_SIZE);
		if (n == -1)
		{
			free(buffer);
			free(ptr);
			return (NULL);
		}
		ptr[n] = '\0';
		buffer = ft_strjoin_gnl(buffer, ptr);
	}
	free(ptr);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[LIMIT];
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = (char *)malloc(1 * sizeof(char));
		buffer[fd][0] = '\0';
	}
	buffer[fd] = read_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	str = next_line(buffer[fd]);
	buffer[fd] = new_line(buffer[fd]);
	return (str);
}
