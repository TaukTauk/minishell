/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:38:11 by talin             #+#    #+#             */
/*   Updated: 2025/01/01 12:30:44 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define MY_IOCTL_CMD 0x1234
int main() {
	int fd = open("test.txt", O_RDONLY);
	
	if (isatty(0)) {
		printf("stdin is a terminal\n");
	} else {
		printf("stdin is not a terminal\n");
	}
	if (isatty(fd)) {
		printf("fd: %d is a terminal\n", fd);
	} else {
		printf("fd: %d is not a terminal\n", fd);
	}
	dup2(1, fd);
	if (isatty(fd)) {
		printf("fd: %d is a terminal\n", fd);
	} else {
		printf("fd: %d is not a terminal\n", fd);
	}
	


	printf("\n\n#####\n\n");
	char *tty;
	int fdd = open("Makefile", O_RDONLY);
	tty = ttyname(0);
	if (tty != NULL) {
		printf("%s\n", tty);
	} else {
		perror("ttyname");
	}
	tty = ttyname(fdd);
	if (tty != NULL) {
		printf("%s\n", tty);
	} else {
		perror("ttyname");
	}
	tty = ttyname(fd);
	if (tty != NULL) {
		printf("%s\n", tty);
	} else {
		perror("ttyname");
	}
	close(fd);
	close(fdd);
	



	printf("\n\n#####\n\n");
	int slot = ttyslot();

	if (slot > 0) {
		printf("current terminal is in slot: %d\n", slot);
	} else {
		printf("no terminal slot found, %s\n", strerror(errno));
	}



	printf("\n\n#####\n\n");
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
		printf("Terminal size: %d rows, %d columns\n", w.ws_row, w.ws_col);
	} else {
		perror("ioctl");
	}

	printf("\n\n#####\n\n");
	int fd2 = open("abc", O_RDWR);
	if (fd2 < 0) {
		perror("open");
		return (1);
	}
	int result = ioctl(fd2, MY_IOCTL_CMD, NULL);
	if (result == -1) {
		perror("ioctl");
	} else {
		printf("IOCTL command exectued successfully.\n");
	}
	close(fd2);
	return(0);
}