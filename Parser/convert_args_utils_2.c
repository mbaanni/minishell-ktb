/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:37:04 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 13:02:39 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_arg(char *str)
{
	int		i;
	char	*arg;

	i = 0;
	while (str[i] && (str[i] != '"' && str[i] != '\''))
		i++;
	arg = ft_substr(str, 0, i);
	return (arg);
}

int	parsing_processing(char *str, char c, int i, char **s2)
{
	char	s[2];

	while (str[i] && str[i] != c)
	{
		s[0] = str[i];
		s[1] = '\0';
		*s2 = ft_strjoin(*s2, s);
		i++;
	}
	if (str[i] && (str[i] == '"' || str[i] == '\''))
		i++;
	while (str[i] && str[i] != '"' && str[i] != '\'')
	{
		s[0] = str[i];
		s[1] = '\0';
		*s2 = ft_strjoin(*s2, s);
		i++;
	}
	return (i);
}

char	*parse_string(char *str)
{
	int		i;
	char	c;
	char	*s2;

	s2 = NULL;
	i = 0;
	if (str[i] != '"' && str[i] != '\'')
		s2 = get_arg(str);
	while (str[i] && str[i] != '"' && str[i] != '\'')
		i++;
	while (str[i])
	{
		c = str[i++];
		i = parsing_processing(str, c, i, &s2);
	}
	if (!s2)
		return (ft_strdup("\0"));
	return (s2);
}

char	**get_args(t_list *cmd)
{
	int		i;
	char	**args;
	t_list	*tmp;

	tmp = cmd;
	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	args = my_alloc(sizeof(char *) * (i + 1));
	if (!args)
		return (0);
	i = 0;
	while (tmp)
	{
		args[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}
