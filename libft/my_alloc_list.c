/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_alloc_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:14:47 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/15 12:15:12 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_myalloc	*my_alloc_new(void *content)
{
	t_myalloc	*newnode;

	newnode = malloc(sizeof(t_myalloc));
	if (!newnode)
		return (0);
	newnode->content = content;
	newnode->next = 0;
	return (newnode);
}

t_myalloc	*alloc_last(t_myalloc *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	my_alloc_addback(t_myalloc **lst, t_myalloc *new)
{
	t_myalloc	*tmp;

	if (*lst)
	{
		tmp = alloc_last(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}

void	my_alloc_clear(t_myalloc **lst)
{
	t_myalloc	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		(*lst) = tmp;
	}
	*lst = NULL;
}
