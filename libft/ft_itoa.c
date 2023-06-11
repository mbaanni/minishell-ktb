/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:06:28 by mtaib             #+#    #+#             */
/*   Updated: 2022/10/29 11:39:18 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	nlen(long int n)
{
	int	c;

	c = 0;
	if (n < 0)
	{
		n *= -1;
		c++;
	}
	if (n == 0)
		c++;
	while (n)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	j;
	long	nb;

	nb = n;
	i = nlen(n);
	str = (char *)my_alloc(sizeof(char) * (nlen(nb) + 1));
	if (!str)
		return (NULL);
	j = 0;
	if (nb < 0)
	{
		nb *= -1;
		str[j] = '-';
		j++;
	}
	str[i] = '\0';
	i--;
	while (i >= j)
	{
		str[i--] = nb % 10 + 48;
		nb = nb / 10;
	}
	return (str);
}
