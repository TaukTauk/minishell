/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:26:55 by talin             #+#    #+#             */
/*   Updated: 2025/03/12 12:28:57 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_shlvl(t_data *data)
{
	t_envp	*temp;
	int		num;

	temp = env_find(data->envp, "SHLVL");
	if (temp)
	{
		num = ft_atoi(temp->value);
		num++;
		free(temp->value);
		temp->value = ft_itoa(num);
		if (!temp->value)
		{
			printf("hi\n");
			perror("ft_itoa");
			exit(EXIT_FAILURE);
		}
	}
}

void	init_shell(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(*data));
	data->env = envp;
	data->status = 0;
	init_env(data);
	update_shlvl(data);
}
