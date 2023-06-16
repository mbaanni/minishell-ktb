/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:36:10 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 17:15:27 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

t_lexim	*expand_wild_card(t_lexim *tmp_lexim, char *astrik)
{
	t_lexim	*tmp_next;
	t_lexim	*tmp_prev;
	t_lexim	*astriks;

	astriks = NULL;
	tmp_prev = NULL;
	tmp_next = NULL;
	if (tmp_lexim->prev)
		tmp_prev = tmp_lexim->prev;
	tmp_lexim = expand_wild_card_utils(tmp_lexim, tmp_next, &astrik);
	if (astrik)
		astriks = find_matching(astrik);
	if (astriks)
	{
		if (tmp_prev)
			tmp_prev->next = astriks;
		while (astriks && astriks->next)
			astriks = astriks->next;
		astriks->next = tmp_next;
	}
	else if (tmp_prev)
		tmp_lexim = tmp_prev->next;
	return (tmp_lexim);
}

void	expand_var_for_redirection(t_redir *tmp_redir)
{
	if (tmp_redir->file[0] == '$')
		tmp_redir->file = ft_split(expand_var(tmp_redir->file), ' ')[0];
	else
		tmp_redir->file = expand_var(tmp_redir->file);
}

void	expand_redirections(t_redir *tmp_redir, char *str)
{
	while (tmp_redir)
	{
		if (tmp_redir->is_expand && tmp_redir->token != HERE_DOC)
		{
			if (tmp_redir->file
				&& !check_ambigious(expand_var(tmp_redir->file)))
			{
				str = expand_var(tmp_redir->file);
				str = parse_string(str);
				if (str && !str[0] && should_parse(tmp_redir->file))
					tmp_redir->file = ft_strdup("\0");
				else
				{
					tmp_redir->is_expand = 2;
					tmp_redir->file = expand_var(tmp_redir->file);
					break ;
				}
			}
			else
				expand_var_for_redirection(tmp_redir);
		}
		tmp_redir = tmp_redir->next;
	}
}

void	expand_args(t_lexim *tmp_lexim, t_lexim *tmp_next)
{
	while (tmp_lexim)
	{
		if (tmp_lexim->prev && tmp_lexim->prev->token == SPACES
			&& tmp_lexim->token == WORD && tmp_lexim->content[0] == '$')
		{
			if (tmp_lexim->content[1] == '@')
				tmp_lexim->content += 2;
			else if (tmp_lexim->content[1] == '$')
			{
				tmp_lexim->content++;
				while ((*tmp_lexim->content) && (*tmp_lexim->content) == '$')
					tmp_lexim->content++;
				if (!*tmp_lexim->content)
					tmp_lexim->content = "$";
			}
		}
		else if (tmp_lexim->token == ENV)
			tmp_lexim = get_value(tmp_lexim, &tmp_next);
		else if (is_wild(tmp_lexim->content))
			tmp_lexim = expand_wild_card(tmp_lexim, NULL);
		if (tmp_lexim)
			tmp_lexim = tmp_lexim->next;
	}
}

t_cmd	*ft_expand(t_cmd *cmds, int nb_cmds)
{
	int		i;
	t_lexim	*tmp_lexim;
	t_redir	*tmp_redir;

	i = 0;
	while (i < nb_cmds)
	{
		tmp_lexim = cmds[i].args;
		tmp_redir = cmds[i].redirs;
		expand_args(tmp_lexim, NULL);
		expand_redirections(tmp_redir, NULL);
		i++;
	}
	return (cmds);
}
