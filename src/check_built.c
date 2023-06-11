/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:29:37 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/08 11:08:33 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/fcntl.h>

int	built_check01(t_command *cm, int i)
{
	if (!ft_strncmp("cd", *cm->command_args, -1))
	{
		if (i)
			ft_cd(cm);
		return (1);
	}
	if (!ft_strncmp("export", *cm->command_args, -1))
	{
		if (i)
			ft_export(cm);
		return (1);
	}
	if (!ft_strncmp("env", *cm->command_args, -1))
	{
		if (i)
			ft_env();
		return (1);
	}
	if (!ft_strncmp("unset", *cm->command_args, -1))
	{
		if (i)
			ft_unset(cm);
		return (1);
	}
	return (0);
}

int	built_check02(t_command *cm, int i)
{
	if (!ft_strncmp("echo", *cm->command_args, -1))
	{
		if (i)
			ft_echo(cm);
		return (1);
	}
	if (!ft_strncmp("exit", *cm->command_args, -1))
	{
		if (i)
			ft_exit(cm);
		return (1);
	}
	if (!ft_strncmp("pwd", *cm->command_args, -1))
	{
		if (i)
			ft_pwd();
		return (1);
	}
	return (0);
}

int	check_for_built_in(t_command *cm, int i)
{
	if (!cm->command_args)
		return 0;
	if (built_check01(cm, i))
		return (1);
	if (built_check02(cm, i))
		return (1);
	return (0);
}
