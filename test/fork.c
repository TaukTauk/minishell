/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:38:44 by talin             #+#    #+#             */
/*   Updated: 2024/12/30 16:13:58 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void) {
	pid_t pids[1024];
	int size = 5;
	for(int i = 0; i < size; i++) {
		pids[i] = fork();
		if (pids[i] < 0){
			perror("fork");
		}
		if (pids[i] == 0) {
			printf("child %d, pid: %d\n", i, getpid());
			exit(0);
		}
		
	}
	for (int i = 0; i < size; i++){
		waitpid(pids[i], NULL, 0);
	}
	printf("parent\n");
	return (0);
}


// int main(){
//     int cpid = fork();
//     int cpid2 = fork();

//     if(cpid != 0 && cpid2 != 0){
//         int status;
//         printf("\nParent: I am going to wait for process with ID: %d\n", cpid2);
            
//         // wait for any child to exit    
//         // int waitPID = wait(&status);

//         // wait for cpid2 to exit
//         int waitPID = waitpid(cpid, &status, 0);

//         printf("\nParent: Waited for child, return value of waitpid(): %d\n", waitPID);
//         printf("\nParent: Exit code of terminated child: %d\n", WEXITSTATUS(status));
//         exit(1);
//     }
//     else if(cpid == 0 && cpid2 != 0){
//         printf("\nChild1: My process ID: %d, my exit code is 1\n", getpid());
//         // sleep(1);
//         exit(1);   
//     }
//     else if(cpid != 0 && cpid2 == 0){
//         printf("\nChild2: My process ID: %d, my exit code is 2\n", getpid());
//         // sleep(1);
//         exit(2);
//     }
//     else{
//         printf("\nChild3: My process ID: %d, my exit code is 3\n", getpid());
//         // sleep(1);
//         exit(39);
//     }

//     return 0;
// }

// int main(void) {
// 	pid_t pid1 = fork();
// 	if (pid1 < 0) {
// 		perror("fork");
// 	}

// 	if (pid1 == 0) {
// 		printf("hello child 1, %d\n", getpid());
// 		sleep(10);
// 	}
// 	if (pid1 > 0) {
// 		pid_t pid2 = fork();
// 		if (pid2 == 0) {
// 			printf("hello child 2, %d\n", getpid());
// 			sleep(10);
// 		}
// 		if (pid2 > 0)
// 		{
// 			wait(NULL);
// 			printf("parent, %d\n", getpid());
// 			sleep(10);
// 		}
// 	}
// 	return (0);
// }
