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

void	add_args(t_lexim *tmp_lexim, char **args)
{
	int	j;

	j = 0;
	while (args[++j])
	{
		tmp_lexim->next = new_lexim(ft_strdup(" "));
		tmp_lexim->next->token = SPACES;
		tmp_lexim->next->next = new_lexim(args[j]);
		if (tmp_lexim->next->next)
			tmp_lexim = tmp_lexim->next->next;
	}
}

void	assign_values(char **args, t_lexim **tmp_lexim)
{
	int	j;

	j = 0;
	while (args[++j])
	{
		(*tmp_lexim)->next = new_lexim(ft_strdup(" "));
		(*tmp_lexim)->next->token = SPACES;
		(*tmp_lexim)->next->next = new_lexim(args[j]);
		if ((*tmp_lexim)->next->next)
			(*tmp_lexim) = (*tmp_lexim)->next->next;
	}
}

t_lexim	*get_value(t_lexim *tmp_lexim, t_lexim **tmp_next)
{
	char	**args;

	args = NULL;
	if (tmp_lexim->content[0] == '"')
		tmp_lexim->content = expand_var(tmp_lexim->content);
	else if (tmp_lexim->content[0] != '"'
		&& !check_ambigious(expand_var(tmp_lexim->content))
		&& !is_space(expand_var(tmp_lexim->content)))
	{
		args = ft_split(expand_var(tmp_lexim->content), ' ');
		(*tmp_next) = tmp_lexim->next;
		tmp_lexim->content = args[0];
		assign_values(args, &tmp_lexim);
		tmp_lexim->next = (*tmp_next);
	}
	else
	{
		if (tmp_lexim->prev && tmp_lexim->prev->token == SPACES)
			tmp_lexim->content = *ft_split(expand_var(tmp_lexim->content), ' ');
		else
			tmp_lexim->content = expand_var(tmp_lexim->content);
	}
	return (tmp_lexim);
}

t_lexim	*expand_env(t_lexim *tmp_lexim)
{
	t_lexim	*tmp_next;
	char	**args;

	args = NULL;
	if (tmp_lexim->content[0] == '"')
		tmp_lexim->content = expand_var(tmp_lexim->content);
	else if (tmp_lexim->content[0] != '"'
		&& !check_ambigious(expand_var(tmp_lexim->content))
		&& !is_space(expand_var(tmp_lexim->content)))
	{
		args = ft_split(expand_var(tmp_lexim->content), ' ');
		tmp_next = tmp_lexim->next;
		tmp_lexim->content = args[0];
		add_args(tmp_lexim, args);
		tmp_lexim->next = tmp_next;
	}
	else
	{
		if (tmp_lexim->prev && tmp_lexim->prev->token == SPACES)
			tmp_lexim->content = *ft_split(expand_var(tmp_lexim->content), ' ');
		else
			tmp_lexim->content = expand_var(tmp_lexim->content);
	}
	return (tmp_lexim);
}

t_lexim	*expand_wild_card_utils(t_lexim *tmp_lexim, t_lexim *tmp_next,
		char **astrik)
{
	tmp_next = tmp_lexim->next;
	while (tmp_next && tmp_next->token == ENV)
		tmp_next = tmp_next->next;
	while (tmp_lexim && tmp_lexim->token != SPACES)
	{
		if (tmp_lexim->token == ENV)
			tmp_lexim = expand_env(tmp_lexim);
		*astrik = ft_strjoin(*astrik, tmp_lexim->content);
		if (tmp_lexim)
			tmp_lexim = tmp_lexim->next;
	}
	return (tmp_lexim);
}
