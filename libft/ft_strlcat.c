/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:53:32 by mtaib             #+#    #+#             */
/*   Updated: 2022/10/29 17:13:13 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strlcat(char *dst,  char *src, int dstsize)
{
	int	i;
	int	j;
	int			dst_len;
	int			src_len;

	dst_len = 0;
	if (dst)
		dst_len = ft_strlen(( char *)dst);
	src_len = ft_strlen(( char *)src);
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	i = 0;
	j = dst_len;
	while (src[i] && ((i + dst_len) < dstsize - 1))
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst_len + src_len);
}
