/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:37:01 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/15 14:39:28 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *str)
{
	t_env	*env;

	env = g_grl->env_head;
	while (env)
	{
		if (!ft_strncmp(env->id, str, -1))
			return (env->data);
		env = env->next;
	}
	return (0);
}

void	ft_pwd(void)
{
	char	*str;

	str = 0;
	str = getcwd(0, 0);
	garbage_collector(str, 0);
	if (!str)
		str = ft_getenv("PWD");
	ft_fdprintf(1, "%s\n", str);
	g_grl->exit_status = 0;
}

void	ft_env(void)
{
	t_env	*ptr;

	ptr = g_grl->env_head;
	while (ptr)
	{
		if (ptr->i)
			ft_fdprintf(1, "%s=%s\n", ptr->id, ptr->data);
		ptr = ptr->next;
	}
	g_grl->exit_status = 0;
}
