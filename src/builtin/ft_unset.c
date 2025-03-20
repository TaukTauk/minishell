/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:23 by talin             #+#    #+#             */
/*   Updated: 2025/03/20 13:35:32 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	unset_env(t_envp **envp, char *key, t_data **data)
{
	t_envp	*current;
	t_envp	*prev;

	current = *envp;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*envp = current->next;
			free(current->key);
			free(current->value);
			free(current);
			(*data)->env_len--;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_unset(t_command *commands, t_data *data)
{
	int	i;

	if (commands->args[1])
	{
		i = 0;
		while (commands->args[++i])
		{
			if (commands->args[i])
			{
				unset_env(&(data->envp), commands->args[i], &data);
			}
		}
	}
}
