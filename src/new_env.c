/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:49:57 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/08 11:22:06 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	list_env_size(t_env *ptr)
{
	int	i;

	i = 0;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

char	**set_new_env(void)
{
	t_env	*env;
	char	**new_env;
	int		i;

	i = 0;
	env = g_grl->env_head;
	new_env = my_alloc(sizeof(char *) * (list_env_size(env) + 1));
	while (env)
	{
		if (env->data)
		{
			new_env[i] = ft_strjoin(env->id, "=");
			new_env[i] = ft_strjoin(new_env[i], env->data);
		}
		env = env->next;
		i++;
	}
	new_env[i] = 0;
	return (new_env);
}
