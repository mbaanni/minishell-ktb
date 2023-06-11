/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:20:24 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/30 16:32:20 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_fdputstr(char *str, int *counter, int fd)
{
	if (str == 0)
		str = "(null)";
	write(fd, str, ft_strlen(str));
	*counter = *counter + ft_strlen(str);
}

void	ft_fdputnbr(long int nb, int *count, int fd)
{
	char	c;

	c = 0;
	if (nb < 0)
	{
		write(fd, "-", 1);
		*count = *count + 1;
		nb = nb * -1;
	}
	if (nb / 10)
		ft_fdputnbr(nb / 10, count, fd);
	c = nb % 10 + 48;
	*count = *count + 1;
	write(fd, &c, 1);
}

void	ft_fdputchar(char c, int *count, int fd)
{
	write(fd, &c, 1);
	*count = *count + 1;
}

void	print_it(char **str, va_list lst, int *counter, int fd)
{
	if (**str == 'c' || **str == 's')
	{
		if (**str == 'c')
			ft_fdputchar(va_arg(lst, int), counter, fd);
		else
			ft_fdputstr(va_arg(lst, char *), counter, fd);
		(*str)++;
	}
	else if (**str == 'd' || **str == 'i' || **str == 'u')
	{
		if (**str == 'u')
			ft_fdputnbr(va_arg(lst, unsigned int), counter, fd);
		else
			ft_fdputnbr(va_arg(lst, int), counter, fd);
		(*str)++;
	}
}

int	ft_fdprintf(int fd, char *str, ...)
{
	va_list	lst;
	int		counter;

	counter = 0;
	va_start(lst, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			print_it(&str, lst, &counter, fd);
		}
		else
		{
			ft_fdputchar(*str, &counter, fd);
			counter++;
			str++;
		}
	}
	va_end(lst);
	return (counter);
}

