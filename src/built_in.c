/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:37:21 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/14 19:55:12 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

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
		if (ptr->i == 1)
			ft_fdprintf(1, "%s=%s\n", ptr->id, ptr->data);
		ptr = ptr->next;
	}
	g_grl->exit_status = 0;
}

int	exit_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\t' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	res = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * 10 + (str[i] - 48);
		else
		{
			ft_fdprintf(2, "minishell: exit: %s: numeric argument required\n",
					str);
			custom_exit(255);
		}
		i++;
	}
	return (res * sign);
}

void	ft_exit(t_command *cmd)
{
	if (!cmd->command_args[1])
		custom_exit(g_grl->exit_status);
	if (cmd->command_args[2])
	{
		exit_atoi(cmd->command_args[1]);
		ft_fdprintf(2, "minishell: exit: too many arguments\n");
		custom_exit(1);
	}
	else
		custom_exit((char)exit_atoi(cmd->command_args[1]));
}
