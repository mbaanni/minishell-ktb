/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:17:56 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/06 13:28:42 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	garbage_collector(void *adress, int arg)
{
	static t_myalloc	*head;
	t_myalloc			*node;

	if (arg)
		my_alloc_clear(&head, free);
	else
	{
		node = my_alloc_new(adress);
		my_alloc_addback(&head, node);
	}
}

void	custom_exit(int exit_code)
{
	garbage_collector(NULL, 1);
	exit(exit_code);
}

void	*my_alloc(int size)
{
	void	*str;

	str = malloc(size);
	if (!str)
		return (0);
	ft_memset(str, 0, size);
	garbage_collector(str, 0);
	return (str);
}
