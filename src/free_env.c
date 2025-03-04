/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:23:21 by talin             #+#    #+#             */
/*   Updated: 2025/03/04 11:23:36 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	free_environ(data->env);
}
