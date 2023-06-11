/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lexims.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:49:53 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/10 17:00:55 by mtaib            ###   ########.fr       */
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

char	*sub_spe_lexim(char *str)
{
	int		i;
	char	*lexim;
	int		j;

	j = 0;
	i = 0;
	if (str[i] == '"' || str[i] == '\'')
		i = count_chars_for_quotes(&str[i]);
	else if (str[i] == '$')
		i = count_chars_for_env(&str[i]);
	else
		i = count_chars_for_rep(&str[i]);
	lexim = my_alloc(i + 1);
	if (!lexim)
		return (0);
	j = 0;
	while (str[j] && j < i)
	{
		lexim[j] = str[j];
		j++;
	}
	lexim[j] = '\0';
	return (lexim);
}

char	*sub_lexim(char *str)
{
	int		i;
	char	*lexim;

	i = 0;
	while (str[i] && !ft_strchr("\"'$ <>|", str[i]))
		i++;
	lexim = my_alloc(i + 1);
	if (!lexim)
		return (0);
	i = 0;
	while (str[i] && !ft_strchr("\"'$ <>|", str[i]))
	{
		lexim[i] = str[i];
		i++;
	}
	lexim[i] = '\0';
	return (lexim);
}

int	special_lexims(char *str, int i, char c, t_lexim **lexims)
{
	t_lexim *tmp;

	add_back(lexims, new_lexim(sub_spe_lexim(&str[i])));
	tmp = *lexims;
	//printf("%s\n",sub_spe_lexim(&str[i]));
	while (tmp && tmp->next)
		tmp = tmp->next;
	int		j;
	(void)c;
	j = 0;
	while (tmp && tmp->content[j])
		j++;
	/*if (ft_strchr("|<>",str[i]))
		while (str[i] && str[i+1] && str[i] == str[i + 1])
			i++;
	else if (str[i] == '$')
	{
		i++;
		while (str[i])
		{
			if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_'
				&& str[i] != '@' && str[i] != '?')
				break ;
			i++;
		}
	}
	else if (str[i] && (str[i] == '\'' || str[i] == '"'))
	{
		while (str[i] && str[i] != ' ' && (str[i] == '\'' || str[i] == '"'))
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i])
				i++;
		}
		c = '1';
	}
	if (ft_strchr("|<>",str[i]) && c != '1')
		i++;*/
	i += j;
	return (i);
}

t_lexim	*convert_to_lexims(char *str)
{
	int		i;
	t_lexim	*lexims;

	lexims = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] && ft_strchr("\"'$<>|", str[i]))
			i = special_lexims(str, i, '\0', &lexims);
		else
		{
			if (str[i])
			{
				add_back(&lexims, new_lexim(sub_lexim(&str[i])));
				while (str[i] && (!ft_strchr("\"'$<>|", str[i])
					&& str[i] != ' '))
					i++;
			}
		}
		if (str[i] && str[i] == ' ')
		{
			add_back(&lexims, new_lexim(ft_strdup(" ")));
			while (str[i] && str[i] == ' ')
				i++;
		}
	}
	/*while (lexims)
	{
		printf("--%s--\n", lexims->content);
		lexims = lexims->next;
	}*/
	tokenize_elements(lexims);
	return (lexims);
}
