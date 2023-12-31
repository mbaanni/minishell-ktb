/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:35:50 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 16:26:47 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
		return (1);
	return (0);
}

int	parse_it(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		c = str[i++];
		while (str[i] && str[i] != c)
		{
			if (c == '"' && str[i] == '$' && (str[i + 1] == '_'
					|| str[i + 1] == '?' || ft_isalpha(str[i + 1])))
				return (1);
			i++;
		}
		i++;
	}
	return (0);
}

void	parse_env(t_lexim *lexims)
{
	while (lexims)
	{
		if (check_env(lexims->content))
		{
			if (lexims->content[0] == '\'' || lexims->content[0] == '"')
			{
				if (parse_it(lexims->content))
					lexims->token = ENV;
				else
					lexims->token = WORD;
			}
		}
		lexims = lexims->next;
	}
}

void	tokenize_lexims(t_lexim *lexims)
{
	if (lexims->content[0] == '|')
		lexims->token = PIPE;
	else if (lexims->content[0] == '<'
		&& (!lexims->content[1] || lexims->content[2]))
		lexims->token = RDIRIN;
	else if (lexims->content[0] == '>' && lexims->content[1] == '>'
		&& !lexims->content[2])
		lexims->token = APPEND;
	else if (lexims->content[0] == '>')
		lexims->token = RDIROUT;
	else if (lexims->content[0] == '<' && ft_strlen(lexims->content) == 2)
		lexims->token = HERE_DOC;
	else if (lexims->content[0] == '$' && (lexims->content[1] == '_'
			|| lexims->content[1] == '?' || ft_isalpha(lexims->content[1])
			|| ft_isdigit(lexims->content[1])))
		lexims->token = ENV;
	else if (lexims->content[0] == ' ')
		lexims->token = SPACES;
	else if (lexims->content[0] == '\t')
		lexims->token = TABS;
	else
	{
		if (lexims->token != ENV)
			lexims->token = WORD;
	}
}

void	tokenize_elements(t_lexim *lexims)
{
	t_lexim	*tmp;

	tmp = lexims;
	parse_env(lexims);
	while (lexims)
	{
		tokenize_lexims(lexims);
		lexims = lexims->next;
	}
	parse_commands(tmp, NULL, -1);
}
