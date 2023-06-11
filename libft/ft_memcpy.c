/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:53:10 by mtaib             #+#    #+#             */
/*   Updated: 2022/10/29 16:19:32 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst,  void *src, int n)
{
	int	i;

	i = -1;
	if (!src && !dst)
		return (0);
	while (++i < n)
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	return ((void *)(dst));
}
