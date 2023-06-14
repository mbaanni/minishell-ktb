/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:25:34 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/14 16:05:35 by mtaib            ###   ########.fr       */
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

void	print_parsing(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (i < g_grl->command_count)
	{
		while (cmds[i].args)
		{
			printf("%s\n", (cmds[i].args)->content);
			cmds[i].args = (cmds[i].args)->next;
		}
		printf("REDIR\n");
		while (cmds[i].redirs)
		{
			printf("%c\n", (cmds[i].redirs)->token);
			printf("%s\n", (cmds[i].redirs)->file);
			printf("is expanded = %d\n", (cmds[i].redirs)->is_expand);
			cmds[i].redirs = (cmds[i].redirs)->next;
		}
		printf("--------\n");
		i++;
	}
}

int		is_expand(char *str)
{
	int		i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '$')
			return (1);
	}
	return (0);
}

int        expand_it(char    *str)
{
    int        i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
            return (0);
        i++;
    }
    return (1);
}

t_lexim    *parse_redirections(t_lexim *lexims, t_redir **redirs)
{
    char    *str;
    t_lexim *tmp;

    str = NULL;
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

t_redir		*last_redir(t_redir *redirs)
{
	while (redirs->next)
		redirs = redirs->next;
	return (redirs);
} 

t_cmd	*parse_commands(t_lexim *lexims)
{
	t_cmd 	*cmds;
	int		i;
	t_lexim *tmp;

	tmp = lexims;
	i = -1;
	g_grl->command_count = n_cmds(lexims);
	cmds = my_alloc(g_grl->command_count * sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	while(++i < g_grl->command_count)
	{
		while (lexims && lexims->token != PIPE)
		{
			if (lexims->token == RDIRIN || lexims->token == RDIROUT 
					|| lexims->token == HERE_DOC  || lexims->token == APPEND)
				lexims = parse_redirections(lexims, &(cmds[i].redirs));
			else
			{
				if (!lexims->is_redir)  
					add_back(&(cmds[i].args), new_lex(lexims->content, lexims->token));
			}
			if (lexims)
				lexims = lexims->next;	
		}
		if (lexims)
			lexims = lexims->next;	
	}
	//print_parsing(cmds);
	//exit(0);
	ft_expand(cmds, g_grl->command_count);
	convert_args(cmds);
	return (cmds);
}
