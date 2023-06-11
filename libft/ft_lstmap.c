/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 08:19:54 by mtaib             #+#    #+#             */
/*   Updated: 2022/10/29 16:56:40 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*newnode;
	t_list	*head;
	t_list	*nextnode;

	if (!lst || !f || !del)
		return (0);
	tmp = lst;
	newnode = ft_lstnew(f(tmp->content));
	if (!newnode)
		return (NULL);
	head = newnode;
	while (tmp)
	{
		if (!newnode)
			del(newnode->content);
		tmp = tmp->next;
		if (!tmp)
			break ;
		nextnode = ft_lstnew(f(tmp->content));
		newnode->next = nextnode;
		newnode = nextnode;
	}
	return (head);
}
