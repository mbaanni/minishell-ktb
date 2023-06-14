/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:57:26 by mtaib             #+#    #+#             */
/*   Updated: 2022/10/29 16:14:45 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	isset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	start_end(char *s1, char *set, int *i, int *j)
{
	while (*j >= 0 && isset(s1[*j], set))
	{
		*j = *j - 1;
	}
	*i = 0;
	while (s1[*i] && isset(s1[*i], set))
	{
		*i = *i + 1;
	}
}

char	*ft_strtrim(char *s1, char *set)
{
	int		j;
	int		i;
	int		len;
	char	*str;
	int		start;

	if (!s1)
		return (NULL);
	j = ft_strlen(s1) - 1;
	start_end(s1, set, &i, &j);
	start = i;
	len = 0;
	while (i++ <= j)
		len++;
	str = (char *)my_alloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start <= j)
	{
		str[i++] = s1[start];
		start++;
	}
	str[i] = '\0';
	return (str);
}
