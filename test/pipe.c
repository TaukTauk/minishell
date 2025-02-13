/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:29:49 by talin             #+#    #+#             */
/*   Updated: 2024/12/30 14:43:40 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define MSGSIZE 16

int main(void) {
	char inbuf[MSGSIZE];
	int p[2], i;

	int fd = open("test.txt", O_WRONLY | O_APPEND);
	if (pipe(p) < 0) {
		perror("pipe");
		exit(1);
	}
	
	write(p[1], "hello, world #1", MSGSIZE);
	write(p[1], "hello, world #2", MSGSIZE);
	write(p[1], "hello, world #3", MSGSIZE);
	
	dup2(fd, 1);
	for (i = 0; i < 3; i++) {
		read(p[0], inbuf, MSGSIZE);
		printf("%s\n", inbuf);
	}

	close(p[0]);
	close(p[1]);
	return (0);
}