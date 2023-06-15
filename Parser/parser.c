/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:25:34 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 12:59:41 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_expand(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '$')
			return (1);
	}
	return (0);
}

int	expand_it(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

t_lexim	*parse_redirections(t_lexim *lexims, t_redir **redirs, char *str)
{
	t_lexim	*tmp;

	if (lexims->next)
	{
		tmp = lexims->next;
		if (lexims->next->next && lexims->next->token == SPACES)
			tmp = lexims->next->next;
		redir_add_back((redirs), new_redir(lexims->token, NULL));
		while (tmp && tmp->token != SPACES && tmp->token != PIPE
			&& tmp->token != RDIROUT && tmp->token != RDIRIN
			&& tmp->token != HERE_DOC)
		{
			str = ft_strjoin(str, tmp->content);
			if (lexims->token == HERE_DOC && expand_it(str))
				last_node(*redirs)->is_expand = 1;
			if (is_expand(str) && lexims->token != HERE_DOC
				&& tmp->token == ENV)
				last_node(*redirs)->is_expand = 1;
			tmp->is_redir = 1;
			tmp = tmp->next;
		}
		last_node(*redirs)->file = str;
	}
	return (lexims);
}

t_redir	*last_redir(t_redir *redirs)
{
	while (redirs->next)
		redirs = redirs->next;
	return (redirs);
}

t_cmd	*parse_commands(t_lexim *lexims, t_cmd *cmds, int i)
{
	g_grl->command_count = n_cmds(lexims);
	cmds = my_alloc(g_grl->command_count * sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	while (++i < g_grl->command_count)
	{
		while (lexims && lexims->token != PIPE)
		{
			if (lexims->token == RDIRIN || lexims->token == RDIROUT
				|| lexims->token == HERE_DOC || lexims->token == APPEND)
				lexims = parse_redirections(lexims, &(cmds[i].redirs), NULL);
			else
				if (!lexims->is_redir)
					add_back(&(cmds[i].args), new_lex(lexims->content,
							lexims->token));
			if (lexims)
				lexims = lexims->next;
		}
		if (lexims)
			lexims = lexims->next;
	}
	ft_expand(cmds, g_grl->command_count);
	convert_args(cmds);
	return (cmds);
}
