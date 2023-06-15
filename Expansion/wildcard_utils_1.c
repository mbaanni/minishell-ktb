/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:29:50 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 18:44:53 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*needle(char *str)
{
	int		i;
	char	*ndl;

	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	ndl = my_alloc(i + 1);
	if (!ndl)
		return (0);
	i = 0;
	while (str[i] && str[i] != '*')
	{
		ndl[i] = str[i];
		i++;
	}
	return (ndl);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_count(char *str)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			c++;
		i++;
	}
	return (c);
}

char	*last_wd_occurence(char *str, char *find)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(find) - 1;
	while (i >= 0 && str[i] && find[i])
	{
		if (str[i] != find[j])
			return (&find[j] + 1);
		i--;
		j--;
	}
	return (&find[j] + 1);
}

int	in_begining(char *pattern, int *i, int *j, char **filename)
{
	char	*str;

	str = needle(&pattern[*i]);
	while (pattern[*i] && pattern[*i] != '*')
		(*i)++;
	if (!pattern[*i])
		return (0);
	while ((*filename)[*j] && str[*j] && (*filename)[*j] == str[*j])
		(*j)++;
	if (*filename)
		(*filename) += *j;
	return (1);
}
