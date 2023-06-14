/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_linked_list_stuff1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:46:06 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/14 21:47:07 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*ft_new_command(char *command_path, char **command_args,
		t_redir *command_redirections, int is_valid)
{
	t_command	*new_command;

	new_command = my_alloc(sizeof(t_command));
	if (!new_command)
		return (0);
	new_command->command_path = command_path;
	new_command->command_args = command_args;
	new_command->command_redirections = command_redirections;
	new_command->is_valid = is_valid;
	new_command->next = NULL;
	return (new_command);
}

t_command	*ft_last_command(t_command *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_command_add_back(t_command **head, t_command *cmd)
{
	t_command	*tmp;

	if (*head)
	{
		tmp = ft_last_command(*head);
		tmp->next = cmd;
	}
	else
		*head = cmd;
}
