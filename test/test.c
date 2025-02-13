/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:14:22 by talin             #+#    #+#             */
/*   Updated: 2025/01/02 16:07:55 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	simulate_output()
{
	printf("\n[Background Task] Output generated!\n");
	rl_on_new_line();
	rl_redisplay();
}

void	replace_with_hello()
{
	rl_replace_line("hello world", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main(void)
{
	char	*input;

	// while (1)
	// {
	input = readline("minishell > ");
	// if (!input)
	// {
	// 	break;
	// }
	if (strcmp(input, "exit") == 0)
	{
		free(input);
		// break;
	}
	if (*input)
	{
		add_history(input);
	}
	if (strcmp(input, "history -c") == 0)
	{
		rl_clear_history();
	}
	if (strcmp(input, "replace") == 0)
	{
		replace_with_hello();
	}
	// sleep(3);
	printf("%s\n", input);	
	// simulate_output();
	free(input);
	// }
	return (0);
}
