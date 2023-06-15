/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:05:05 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 12:10:39 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	dell_node(t_myalloc **head, t_myalloc *tmp)
{
	if (tmp == 0)
	{
		tmp = (*head)->next;
		free((*head)->content);
		(*head)->content = 0;
		free(*head);
		*head = tmp;
	}
	else
	{
		tmp = (*head)->next;
		free((*head)->content);
		free((*head));
		*head = tmp;
	}
}

void	ft_myalloc_dell(void *node)
{
	t_myalloc	*tmp;
	t_myalloc	**head;

	head = garbage_collector(0, 2);
	tmp = 0;
	while (*head)
	{
		if ((*head)->content == node)
		{
			dell_node(head, tmp);
			break ;
		}
		tmp = *head;
		head = &(*head)->next;
	}
}
