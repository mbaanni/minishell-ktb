/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:25:34 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 12:59:28 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexim	*new_lex(char *str, t_token type)
{
	t_lexim	*new_lexim;

	new_lexim = my_alloc(sizeof(t_lexim));
	if (!new_lexim)
		return (0);
	new_lexim->content = str;
	new_lexim->token = type;
	new_lexim->prev = 0;
	new_lexim->next = 0;
	return (new_lexim);
}

t_redir	*new_redir(t_token token, char *file)
{
	t_redir	*new_redir;

	new_redir = my_alloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->token = token;
	new_redir->file = file;
	new_redir->is_expand = 0;
	new_redir->next = 0;
	return (new_redir);
}

void	redir_add_back(t_redir **head, t_redir *redir)
{
	t_redir	*tmp;

	if (!*head)
	{
		*head = redir;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
}

int	n_cmds(t_lexim *lexims)
{
	int	i;

	i = 1;
	while (lexims)
	{
		if (lexims->token == PIPE)
			i++;
		lexims = lexims->next;
	}
	return (i);
}

t_redir	*last_node(t_redir *redirs)
{
	while (redirs->next)
		redirs = redirs->next;
	return (redirs);
}
