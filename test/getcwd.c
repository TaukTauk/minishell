/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:24:43 by talin             #+#    #+#             */
/*   Updated: 2025/01/23 15:49:17 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int ac, char **av) {

	// struct stat fileStat;

	// if (lstat("test.sh", &fileStat) < 0) {
	// 	perror("lstat");
	// 	return (1);
	// }

	// printf("Perm: %o, UID: %d, GID: %d, Links: %ld, Size: %ld\n", fileStat.st_mode & 0777, fileStat.st_uid, fileStat.st_gid, fileStat.st_nlink, fileStat.st_size);


	// int fd = open("test.sh", O_RDONLY);
	// if (fd < 0) {
	// 	perror("open");
	// 	return (1);
	// }
	
	// struct stat fStat;
	// if (fstat(fd, &fStat) < 0) {
	// 	perror("fstat");
	// 	close(fd);
	// 	return (1);
	// }
	// printf("Perm: %o, UID: %d, GID: %d, Links: %ld, Size: %ld\n", fStat.st_mode & 0777, fStat.st_uid, fStat.st_gid, fStat.st_nlink, fStat.st_size);
	// close(fd);
	
	char *buf;
	(void)ac;
	buf = getcwd(NULL, 0);
	if (buf != NULL) {
		printf("%s\n", buf);
		if (chdir(av[1]) != 0)
			perror("chdir() failed");
		buf = getcwd(NULL, 0);
		if (buf != NULL)
		{
			printf("%s\n", buf);
			free(buf);
		}
		
	} else {
		perror("getcwd");
		return(1);
	}
	return(0);
}

// int main(void){
// 	char *ptr;
// 	char *buf;
// 	size_t size = 1024;
// 	buf = NULL;
// 	buf = realloc(buf, size);
// 	ptr = getcwd(buf, size);
// 	printf("%s\n", ptr);
// 	free(buf);
// 	return(0);
// }

// int main(void) {
// 	long path_max;
// 	size_t size;
// 	char *buf;
// 	char *ptr;

// 	path_max = pathconf(".", _PC_PATH_MAX);
// 	if (path_max == -1)
// 		size = 1024;
// 	else if (path_max > 10240)
// 		size = 10240;
// 	else
// 		size = path_max;

// 	for (buf = ptr = NULL; ptr == NULL; size *= 2)
// 	{
// 		if ((buf = realloc(buf, size)) == NULL)
// 		{
// 			printf("memleak\n");
// 		}
// 		ptr = getcwd(buf, size);
// 		if (ptr == NULL && errno != ERANGE)
// 		{
// 			printf("ptr memleak\n");
// 		}
// 	}
// 	printf("%s\n", ptr);
// 	free (buf);
// 	return (0);
// }