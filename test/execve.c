/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:08:06 by talin             #+#    #+#             */
/*   Updated: 2024/12/30 13:11:36 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void) {
	pid_t pid = fork();

	if (pid < 0) {
		perror("fork");
	}
	if (pid == 0) {
		char *argv[] = {"/bin/ls", "-l", NULL};
		char *env[] = {NULL};
		if (execve("/bin/ls", argv, env) == -1) {
			perror("execve");
		}
	} else if (pid > 0) {
		wait(NULL);
		printf("child process completed\n");
	}
	return (0);
}