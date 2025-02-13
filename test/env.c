/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:18:38 by talin             #+#    #+#             */
/*   Updated: 2025/01/22 09:52:53 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main() {
	const char *name = "PATH";
	const char *env_p = getenv(NULL);
	if (env_p) {
		printf("Your %s is %s\n", name, env_p);
	}

	struct termios oldt, newt;
	if (tcgetattr(STDIN_FILENO, &oldt) != 0) {
		perror("tcgetattr");
		return (1);
	}
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) != 0){
		perror("tcsetattr");
		return (1);
	}
	printf("Type something (press ENTER to see it, no echoing):\n");
	char ch;
	while (read(STDIN_FILENO, &ch, 1) > 0 && ch != '\n') {
		printf("You typed: %c\n", ch);
	}
	
	if (tcsetattr(STDIN_FILENO, TCSANOW, &oldt) != 0) {
		perror("tcsetattr");
		return (1);
	}

	struct termios t;
	if (tcgetattr(STDIN_FILENO, &t) != 0) {
		perror("tcgetattr");
		return (1);
	}
	printf("Input flags: %x\n", t.c_iflag);
	printf("Output flags: %x\n", t.c_oflag);
	printf("Control flags: %x\n", t.c_cflag);
	printf("Local flags: %x\n", t.c_lflag);
	return (0);
}