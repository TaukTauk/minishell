/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:05:22 by talin             #+#    #+#             */
/*   Updated: 2024/12/29 16:14:16 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void signal_handler(int sig) {
	if (sig == SIGUSR1) {
		printf("Received SIGUSR1\n");
	} else if (sig == SIGUSR2) {
		printf("Received SIGUSR2\n");
		exit(0);
	}
}

void	handler_sigint(int sig, siginfo_t *info, void *context){
	printf("caught sigint %d\n", sig);
	printf("signal sent by process %d\n", info->si_pid);
	printf("signal code: %d\n", info->si_code);
	(void)context;
	exit(0);
}

int main() {
	struct sigaction sa;

	sa.sa_sigaction = handler_sigint;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGTERM, &sa, NULL) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	printf("kill -SIGTERM %d\n", getpid());
	while (1);
	return(0);
	
}