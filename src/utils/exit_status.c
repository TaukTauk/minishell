/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:46:50 by rick              #+#    #+#             */
/*   Updated: 2025/03/17 13:16:02 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_signal_error(const char *message)
{
	ft_putstr_fd((char *)message, STDERR_FILENO);
}

static void	handle_execution_status_two(int status)
{
	if (status == SIGBUS)
		ft_signal_error("Bus error (core dumped)\n");
	else if (status == SIGFPE)
		ft_signal_error("Floating point exception (core dumped)\n");
	else if (status == SIGSEGV)
		ft_signal_error("Segmentation fault (core dumped)\n");
	else if (status == SIGPIPE)
		ft_signal_error("Broken pipe\n");
	else if (status == SIGALRM)
		ft_signal_error("Alarm clock\n");
	else if (status == SIGTTIN)
		ft_signal_error("Stopped (tty input)\n");
	else if (status == SIGTTOU)
		ft_signal_error("Stopped (tty output)\n");
	else if (status == SIGXCPU)
		ft_signal_error("CPU time limit exceeded\n");
	else if (status == SIGXFSZ)
		ft_signal_error("File size limit exceeded\n");
	else if (status == SIGPWR)
		ft_signal_error("Power failure\n");
	else if (status == SIGSYS)
		ft_signal_error("Bad system call (core dumped)\n");
}

void	handle_execution_status(pid_t pid, t_data *data)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->status = 128 + WTERMSIG(status);
	if (status > 128)
		status = status - 128;
	if (status == SIGHUP)
		ft_signal_error("Hangup\n");
	else if (status == SIGQUIT)
		ft_signal_error("Quit (core dumped)\n");
	else if (status == SIGILL)
		ft_signal_error("Illegal instruction (core dumped)\n");
	else if (status == SIGTRAP)
		ft_signal_error("Trace/breakpoint trap (core dumped)\n");
	else if (status == SIGABRT)
		ft_signal_error("Aborted (core dumped)\n");
	else
		handle_execution_status_two(status);
}

void	update_exit_status(pid_t pid, int fd[2], t_data *data)
{
	int		status;

	waitpid(pid, &status, 0);
	close(fd[0]);
	if (WIFEXITED(status))
		data->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->status = 128 + WTERMSIG(status);
}
