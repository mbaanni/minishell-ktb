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

int	in_middle(char *pattern, int *i, int *j, char **filename)
{
	char	*str;

	if (!pattern[*i])
		return (0);
	str = needle(&pattern[*i]);
	*filename = ft_strchr(*filename, pattern[*i]);
	if (check_astrik(&pattern[*i]))
	{
		while (*filename && (*filename)[*j] && str[*j]
			&& (*filename)[*j] == str[*j])
			(*j)++;
		if (*filename)
			(*filename) += *j;
	}
	while (pattern[*i] && pattern[*i] != '*')
		(*i)++;
	return (1);
}

int	process_pattern(char *pattern, int *i, int j, char **filename)
{
	if (!check_astrik(&pattern[*i]))
	{
		if (ft_strcmp(last_wd_occurence(&pattern[*i], *filename),
				&pattern[*i]))
			return (0);
		return (1);
	}
	else if (*i == 0 && !ft_strncmp(*filename, needle(&pattern[*i]),
			check_astrik(&pattern[*i])))
	{
		if (!in_begining(pattern, i, &j, filename))
			return (0);
	}
	else if (*i > 0 && ft_strnstr(*filename, needle(&pattern[*i]),
			ft_strlen(*filename)) && (pattern[*i] != (*filename)[0]
		|| ft_strchr(*filename, pattern[*i])))
	{
		if (!in_middle(pattern, i, &j, filename))
			return (0);
	}
	else
		return (0);
	return (-1);
}

void	skip_astrik(char *pattern, int *i, int *s)
{
	if (pattern[*i] && pattern[*i] == '*')
	{
		(*s)++;
		(*i)++;
	}
}

int	matchpattern(char *pattern, char *filename)
{
	int	i;
	int	s;
	int	count;
	int	val;

	count = ft_count(pattern);
	s = 0;
	i = 0;
	if (pattern && pattern[0] == '*' && !pattern[1])
		return (1);
	while (pattern[i])
	{
		if (pattern[i] != '*')
		{
			val = process_pattern(pattern, &i, 0, &filename);
			if (val != -1)
				return (val);
			s++;
		}
		skip_astrik(pattern, &i, &s);
	}
	if (pattern[0] && s >= count)
		return (1);
	return (0);
}

t_lexim	*find_matching(char *pattern)
{
	t_lexim	*matches;
	t_lexim	*tmp;

	tmp = NULL;
	matches = NULL;
	g_grl->dir = opendir(".");
	if (!g_grl->dir)
		return (matches);
	while (1)
	{
		g_grl->ent = readdir(g_grl->dir);
		if (!g_grl->ent)
			break ;
		if (matchpattern(pattern, g_grl->ent->d_name))
		{
			if (g_grl->ent->d_name[0] == '.' && pattern[0] != '.')
				continue ;
			add_back(&matches, new_lexim(g_grl->ent->d_name));
			tmp = new_lexim(" ");
			add_back(&matches, tmp);
			tmp->token = SPACES;
		}
	}
	return (matches);
}
