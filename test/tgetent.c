/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgetent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:58:52 by talin             #+#    #+#             */
/*   Updated: 2025/01/01 15:11:22 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main() {
	char *termtype = getenv("TERM");
	if (termtype == NULL) {
		fprintf(stderr, "TERM env variable not set\n");
		return (1);
	}

	char buffer[2048];
	if (tgetent(buffer, termtype) <= 0) {
		fprintf(stderr, "Failed to initialize terminal capabilities\n");
	}

	char *move_cursor = tgetstr("cm", NULL);
	if (move_cursor != NULL) {
		char *cursor_position = tgoto(move_cursor, 10, 5);
		if (cursor_position != NULL) {
			tputs(cursor_position, 1, putchar);
		} else {
			fprintf(stderr, "Failed to generate cursor position string.\n");
		}
	
	}
	else {
		fprintf(stderr, "cursor movement capability not found\n");
	}
	return (0);
}

// int main() {
// 	char *termtype = getenv("TERM");
// 	if (termtype == NULL) {
// 		printf("Term environment variable not set. %s\n", strerror(errno));
// 		return (1);
// 	}
// 	char buffer[2048];
// 	int result = tgetent(buffer, termtype);
// 	if (result == 0) {
// 		printf("Terminal type %s not found\n", termtype);
// 		return (1);
// 	}
// 	else if (result == -1) {
// 		perror("Error initializing terminal capabilities");
// 		return (1);
// 	}
// 	printf("==>%s\n", buffer);
// 	// char *buf = tgetstr("cl", NULL);
// 	// if (buf != NULL) {
// 	// 	printf("Clear screen capability: %s\n", buf);
// 	// } else {
// 	// 	printf("No clear screen capability available\n");
// 	// }
// }