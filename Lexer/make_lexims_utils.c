/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lexims_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:49:53 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 12:56:28 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_back(t_lexim **head, t_lexim *new_lexim)
{
	t_lexim	*tmp;

	if (!*head)
	{
		*head = new_lexim;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_lexim;
	new_lexim->prev = tmp;
}

t_lexim	*new_lexim(char *str)
{
	t_lexim	*new_lexim;

	new_lexim = my_alloc(sizeof(t_lexim));
	if (!new_lexim)
		return (0);
	new_lexim->content = str;
	new_lexim->prev = 0;
	new_lexim->is_redir = 0;
	new_lexim->next = 0;
	return (new_lexim);
}

int	count_chars_for_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[1];
	if (str[i] == '"' || str[i] == '\'')
	{
		while (str[i] && str[i] != ' ' && (str[i] == '\'' || str[i] == '"'))
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			i++;
		}
	}
	return (i);
}

int	count_chars_for_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'
			|| str[i] == '$' || str[i] == '@' || str[i] == '?'))
	{
		i++;
		if (str[i] == '$')
			break ;
	}
	return (i);
}

int	count_chars_for_rep(char *str)
{
	int		i;
	char	c;

	c = str[1];
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	if (!i)
		i++;
	return (i);
}
