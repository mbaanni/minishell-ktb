/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:28:06 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/08 11:19:54 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_env_exp(char *str)
{
	char	*old;
	t_env	*exp;

	exp = general->env_head;
	old = getcwd(0, 0);
	old = ft_strjoin("=", old);
	if (chdir(str) == -1)
	{
		ft_fdprintf(2, "minishell: cd: %s: Not a directory\n", str);
		general->exit_status = 1;
		return ;
	}
	str = getcwd(0, 0);
	str = ft_strjoin("=", str);
	while (exp)
	{
		if (!ft_strncmp(exp->id, "PWD", -1))
				exp->data = str;
		if (!ft_strncmp(exp->id, "OLDPWD", -1))
				exp->data = old;
		exp = exp->next;
	}
	
}

void	print_error(char *str)
{
	ft_fdprintf(2, "minishell: cd: %s: No such file or directory\n", str);
	general->exit_status = 1;
}

void	ft_cd(t_command *cmds)
{
	char	*str;

	str = 0;
	general->exit_status = 0;
	if (!cmds->command_args[1])
	{
		str = ft_getenv("HOME");
		if (!str)
		{
			ft_fdprintf(2, "minishell: cd: HOME not set\n");
			general->exit_status = 1;
		}
		else if (!access(str, F_OK))
			change_env_exp(str);
		else
			print_error(str);
		return ;
	}
	str = cmds->command_args[1];
	if (!access(str, F_OK))
		change_env_exp(str);
	else
		print_error(str);
}
