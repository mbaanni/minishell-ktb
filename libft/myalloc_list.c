

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

t_myalloc	*my_alloc_last(t_myalloc *lst)
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
		tmp = my_alloc_last(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}


void	my_alloc_clear(t_myalloc **lst, void (*del)(void *))
{
	t_myalloc	*tmp;

	if (!del || !lst)
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

