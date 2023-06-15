/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:37:04 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 13:02:39 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*new_cmd(char **args)
{
	t_command	*cmd;

	cmd = my_alloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->command_args = args;
	cmd->next = NULL;
	return (cmd);
}

void	cmdadd_back(t_command **cmds, t_command *newcmd)
{
	t_command	*tmp;

	tmp = *cmds;
	if (!*cmds)
	{
		*cmds = newcmd;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newcmd;
}
