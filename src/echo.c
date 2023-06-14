/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:32:13 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/14 18:33:06 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_n(t_command *cmds, int *i)
{
	int	k;

	k = 1;
	*i = 1;
	while (cmds->command_args[*i])
	{
		if (cmds->command_args[*i][0] != '-')
			break ;
		while (cmds->command_args[*i][k])
		{
			if (cmds->command_args[*i][k] != 'n')
			{
				if (*i == 1)
					return (1);
			}
			k++;
		}
		(*i)++;
	}
	if (*i == 1)
		return (1);
	return (0);
}

void	ft_echo(t_command *cmds)
{
	int	nlflag;
	int	i;

	nlflag = check_for_n(cmds, &i);
	while (cmds->command_args[i])
	{
		ft_fdprintf(1, "%s", cmds->command_args[i]);
		i++;
		if (cmds->command_args[i])
			ft_fdprintf(1, " ");
	}
	if (nlflag)
		ft_fdprintf(1, "\n");
	g_grl->exit_status = 0;
}
