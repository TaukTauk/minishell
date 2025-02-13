/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:24:48 by talin             #+#    #+#             */
/*   Updated: 2025/01/01 11:30:36 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void) {
	int fd = open("hello.txt", O_RDONLY);

	if (fd < 0) {
		printf("Error: %s\n", strerror(errno));
		perror("Error");
	}
	close(fd);
	return (0);
}