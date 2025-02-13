/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:16:22 by talin             #+#    #+#             */
/*   Updated: 2024/12/30 16:37:55 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void) {
	char *buf;
	buf = getcwd(NULL, 0);
	DIR *dir = opendir(buf);
	if (dir == NULL) {
		perror("failed to open directory");
		return (1);
	}
	struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s			", entry->d_name);  // Print the name of the entry

        switch (entry->d_type) {
            case DT_REG:
                printf("Regular file\n");
                break;
            case DT_DIR:
                printf("Directory\n");
                break;
            case DT_LNK:
                printf("Symbolic link\n");
                break;
            case DT_FIFO:
                printf("FIFO (named pipe)\n");
                break;
            case DT_SOCK:
                printf("Unix domain socket\n");
                break;
            case DT_CHR:
                printf("Character device\n");
                break;
            case DT_BLK:
                printf("Block device\n");
                break;
            default:
                printf("Unknown\n");
                break;
        }
	}
	closedir(dir);
	free(buf);
	return (0);
}
