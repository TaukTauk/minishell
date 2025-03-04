/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:26:55 by talin             #+#    #+#             */
/*   Updated: 2025/03/04 11:27:22 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
