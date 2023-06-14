/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:56:42 by mtaib             #+#    #+#             */
/*   Updated: 2022/10/29 13:01:01 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(char *haystack, char *needle, int len)
{
	int	i;
	int	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)(haystack));
	if (len == 0 && !haystack)
		return (0);
	while (*haystack && i < len)
	{
		j = 0;
		while ((haystack[j] == needle[j]) && haystack[j] && needle[j] && i
			+ j < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)(haystack));
			j++;
		}
		haystack++;
		i++;
	}
	return (0);
}
