/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_linked_list_stuff.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:11:40 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/14 21:45:52 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
