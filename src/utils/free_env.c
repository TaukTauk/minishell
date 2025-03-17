/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:23:21 by talin             #+#    #+#             */
/*   Updated: 2025/03/15 22:31:16 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_environ(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i])
			free(envp[i]);
		i++;
	}
	if (envp)
		free(envp);
}

void	free_env(t_data *data)
{
	t_envp	*temp;

	if (data->envp)
	{
		while (data->envp)
		{
			temp = data->envp;
			data->envp = data->envp->next;
			if (temp->key)
				free(temp->key);
			if (temp->value)
				free(temp->value);
			if (temp)
				free(temp);
		}
		free(data->envp);
	}
	if (data->env)
		free_environ(data->env);
}
