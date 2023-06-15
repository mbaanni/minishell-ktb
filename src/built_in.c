/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:37:21 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/15 15:00:01 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

static void	print_error(char *str)
{
	ft_fdprintf(2, "minishell: exit: %s: numeric argument required\n",
		str);
	custom_exit(255);
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
			print_error(str);
		i++;
	}
	return (res * sign);
}

void	ft_exit(t_command *cmd)
{
	if (isatty(0))
		write(1, "exit\n", 5);
	if (!cmd->command_args[1])
		custom_exit(g_grl->exit_status);
	if (cmd->command_args[2])
	{
		exit_atoi(cmd->command_args[1]);
		ft_fdprintf(2, "minishell: exit: too many arguments\n");
		g_grl->exit_status = 1;
	}
	else
		custom_exit((char)exit_atoi(cmd->command_args[1]));
}
