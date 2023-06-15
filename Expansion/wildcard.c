/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:29:50 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 13:11:03 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h>

int		check_astrik(char	*str)
{
	int		i;
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (i);
		i++;
	}
	return (0);
}

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

int		ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int		ft_count(char *str)
{
	int		i;
	int		c;

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
	int		i;
	int		j;


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

int matchpattern(char *pattern,char *filename) 
{
	int		i;
	int		s;
	int		count;
	int		j;
	char	*str;

	count = ft_count(pattern);
	s = 0;
	i = 0;
	if (pattern && pattern[0] == '*' && !pattern[1])
		return (1);
	while (pattern[i])
	{
		j = 0;
		if (pattern[i] != '*')
		{
			if (!check_astrik(&pattern[i]))
			{
				if (ft_strcmp(last_wd_occurence(&pattern[i], filename), &pattern[i]))
					return (0);
				return (1);
			}
			else if (i == 0 && !ft_strncmp(filename, needle(&pattern[i]), check_astrik(&pattern[i])))
			{
				str = needle(&pattern[i]);
				while (pattern[i] && pattern[i] != '*')
					i++;
				if (!pattern[i])
					break;
				while (filename[j] && str[j] && filename[j] == str[j])
					j++;
				if (filename)
				{
					filename+=j;
				}
			}
			else if (i > 0 
					&& ft_strnstr(filename, needle(&pattern[i]), ft_strlen(filename))
					&& (pattern[i] != filename[0] || ft_strchr(filename,pattern[i])))
			{
				if (!pattern[i])
					break;
				str = needle(&pattern[i]);
				filename = ft_strchr(filename, pattern[i]);
				if (check_astrik(&pattern[i]))
				{
					while (filename && filename[j] && str[j] && filename[j] == str[j])
						j++;
					if (filename)
					{
						filename+=j;
					}
				}
				while (pattern[i] && pattern[i] != '*')
				{
					i++;
				}
			}
			else
				return (0);
			s++;
		}
		if (pattern[i] && pattern[i] == '*')
		{
			s++;
			i++;
		}
		//printf
	}
	if (pattern[0] && s >= count)
		return (1);
	return (0);
}

t_lexim		*find_matching(char *pattern)
{
    DIR *dir;
    struct dirent *ent;
	t_lexim		*matches;
	t_lexim 	*tmp;

	tmp = NULL;	
	matches = NULL;
	if ((dir = opendir(".")) != NULL) 
	{
        while ((ent = readdir(dir)) != NULL) 
		{
            if (matchpattern(pattern, ent->d_name)) 
			{
				if (ent->d_name[0] == '.' && pattern[0] != '.')
					continue ;
				add_back(&matches, new_lexim(ent->d_name));
				tmp = new_lexim(" ");
				add_back(&matches, tmp);
				tmp->token = SPACES;
			}
		}
	}
    closedir(dir);
	return (matches);
}
