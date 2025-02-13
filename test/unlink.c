/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:16:14 by talin             #+#    #+#             */
/*   Updated: 2024/12/30 12:17:32 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void) {
	const char *filename = "test.sh";

	if (unlink(filename) == 0 ){
		printf("file %s deleted successfully.\n", filename);
	} else {
		perror("unlink");
	}
	return (0);
}
