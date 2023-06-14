/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_linked_list_stuff.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:11:40 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/06 13:40:22 by mbaanni          ###   ########.fr       */
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

int	ft_commands_size(t_command *lst)
{
	int			i;
	t_command	*tmp;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

t_redir	*generate_cmd_redirs(int type, char *file_name)
{
	t_redir	*new;

	new = my_alloc(sizeof(t_redir));
	new->token = type;
	new->file = file_name;
	new->is_expand = 1;
	new->next = 0;
	return (new);
}

t_redir	*ft_last_redir(t_redir *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
void	ft_redir_add_back(t_redir **head, t_redir *cmd)
{
	t_redir	*tmp;

	if (*head)
	{
		tmp = ft_last_redir(*head);
		tmp->next = cmd;
	}
	else
		*head = cmd;
}
