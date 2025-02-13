/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:42:21 by talin             #+#    #+#             */
/*   Updated: 2024/12/30 14:03:07 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void) {
	int fd = open("test.txt", O_WRONLY | O_APPEND);

	int fd2 = dup(fd);
	printf("fd1: %d, fd2: %d\n", fd, fd2);
	
	write(fd, "Hello world!\n", 13);
	write(fd2, "Hi!\n", 4);
	return (0);
}

// int main(void) {
// 	int fd = open("test.txt", O_WRONLY | O_APPEND);

// 	dup2(fd, 1);
// 	write(1, "hi\n", 3);
// 	write(fd, "Hello world!\n", 13);
// 	return (0);
// }