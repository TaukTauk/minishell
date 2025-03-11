/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhtoo-h <juhtoo-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:23:21 by talin             #+#    #+#             */
/*   Updated: 2025/03/11 15:38:57 by juhtoo-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_environ(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	// ft_printf("Freed ENV\n");
}

void	free_env(t_data *data)
{
	t_envp	*temp;

	while (data->envp)
	{
		temp = data->envp;
		data->envp = data->envp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	free(data->envp);
	free_environ(data->env);
	// ft_printf("Freed Env & ENVP\n");
}
