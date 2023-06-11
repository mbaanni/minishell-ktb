/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 10:49:33 by mtaib             #+#    #+#             */
/*   Updated: 2022/10/29 11:31:35 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char  *s, unsigned int start, int len)
{
	unsigned char	*str;
	unsigned char	*ptr;
	int			j;
	int			i;

	ptr = (unsigned char *)s;
	if (!s)
		return (0);
	if ((int)start >= ft_strlen(s))
		return (my_alloc(1));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str = my_alloc(len + 1);
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (ptr[i] && j < len)
	{
		str[j] = ptr[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return ((char *)str);
}
