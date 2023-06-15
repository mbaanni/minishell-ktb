/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:36:10 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 11:52:23 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

char	*sub_keycode(char	*str)
{
	int		i;
	char	*keycode;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	keycode = my_alloc(i + 1);
	if (!keycode)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		keycode[i] = str[i];
		i++;
	}
	keycode[i] = '\0';
	return (keycode);
}

void	replace_str(char *str)
{
	int		i;
	int		state;

	state = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			state = 0;
			i++;
		}
		while (str[i] && !state && str[i] != '"' && str[i] != '\'')
			i++;
		if (!state)
			i++;
		if (str[i] && str[i] != '"' && str[i] != '\'')
			state = 1;
		if (state && str[i] == ' ')
			str[i] = 1;
		if (state)
			i++;
	}
}

int		check_ambigious(char *str)
{
	char	**args;
	int		i;
	int		count;

	count = 0;
	replace_str(str);
	args = ft_split(str, 1);
	//printf("--str ==%s--\n",str);
	//printf("here = ---%s---\n",args[1]);
	
	/*if (args[0] && !args[1] && !parse_string(args[0])[0])
		return (0);
	if (args[1] != NULL || !args[0])
		return (0);*/
	if (!args[0])
		return (0);
	i = 0;
	while (args && args[i])
	{
		if (parse_string(args[i])[0])
			count++;				
		i++;
	}
	if (count > 1 || !count)
		return (0);
	return (1);
}

int		is_space(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	if (!i)
		return (0);
	return (1);
}

int		is_wild(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '"' || str[i] == '\'')
		return (0);
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

t_lexim *expand_env(t_lexim *tmp_lexim)
{
	int		j;
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
		j = 0;
		while (args[++j])
		{
			tmp_lexim->next = new_lexim(ft_strdup(" "));
			tmp_lexim->next->token = SPACES;
			tmp_lexim->next->next = new_lexim(args[j]);
			if (tmp_lexim->next->next)
				tmp_lexim = tmp_lexim->next->next;
		}
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

t_cmd	*ft_expand(t_cmd *cmds, int nb_cmds)
{
	int		i;
	t_env	*envs;
	t_cmd	*tmp;
	t_lexim	*tmp_lexim;
	t_redir	*tmp_redir;
	t_lexim	*tmp_next;
	t_lexim	*tmp_prev;
	char	**args;
	int		j;
	char	*str;
	char	*astrik;
	t_lexim	*astriks;

	astriks = NULL;
	astrik = NULL;
	i = 0;
	envs = g_grl->env_head;
	tmp = cmds;
	while (i < nb_cmds)
	{
		tmp_prev = NULL;
		tmp_next = NULL;
		tmp_lexim = cmds[i].args;
		tmp_redir = cmds[i].redirs;
		while (tmp_lexim)
		{
			if (tmp_lexim->prev 
					&& tmp_lexim->prev->token == SPACES 
					&& tmp_lexim->token == WORD 
					&& tmp_lexim->content[0] == '$')
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
			{
				if (tmp_lexim->content[0] == '"')
				{
					tmp_lexim->content = expand_var(tmp_lexim->content);
				}
				else if (tmp_lexim->content[0] != '"' 
						&& !check_ambigious(expand_var(tmp_lexim->content)) 
						&& !is_space(expand_var(tmp_lexim->content)))
				{
					args = ft_split(expand_var(tmp_lexim->content), ' ');
					j = -1;
					tmp_next = tmp_lexim->next;
					tmp_lexim->content = args[0];
					j = 0;
					while (args[++j])	
					{
							tmp_lexim->next = new_lexim(ft_strdup(" "));
							tmp_lexim->next->token = SPACES;	
							tmp_lexim->next->next = new_lexim(args[j]);
							if (tmp_lexim->next->next)	
								tmp_lexim = tmp_lexim->next->next;
					}
					tmp_lexim->next = tmp_next;
				}
				else
				{
						if (tmp_lexim->prev && tmp_lexim->prev->token == SPACES)
						{
							tmp_lexim->content = *ft_split(expand_var(tmp_lexim->content), ' ');
						}
						else
						{
							tmp_lexim->content = expand_var(tmp_lexim->content);
						}
				}
			}
			else if (is_wild(tmp_lexim->content))
			{
				if (tmp_lexim->prev)
					tmp_prev = tmp_lexim->prev;
				tmp_next = tmp_lexim->next;
				while (tmp_next && tmp_next->token == ENV)
					tmp_next = tmp_next->next;
				while (tmp_lexim && tmp_lexim->token != SPACES)
				{
					if (tmp_lexim->token == ENV)
						tmp_lexim = expand_env(tmp_lexim);
					astrik = ft_strjoin(astrik, tmp_lexim->content);
					if (tmp_lexim)
						tmp_lexim = tmp_lexim->next;
				}
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
				else
				{
					if (tmp_prev)
						tmp_lexim = tmp_prev->next;
				}
			}
			if (tmp_lexim)
				tmp_lexim = tmp_lexim->next;
		}
		while (tmp_redir)
		{
			if (tmp_redir->is_expand && tmp_redir->token != HERE_DOC)
			{
				if (tmp_redir->file && !check_ambigious(expand_var(tmp_redir->file)))
					{
						str = expand_var(tmp_redir->file);
						// if (str)
						str = parse_string(str);
						
						if (str && !str[0] && should_parse(tmp_redir->file))
								tmp_redir->file = ft_strdup("\0");
						else
							{
								tmp_redir->is_expand = 2;
				 				tmp_redir->file = expand_var(tmp_redir->file);
								break;
							}
					}	
				else
				{
					if (tmp_redir->file[0] == '$')
						tmp_redir->file = ft_split(expand_var(tmp_redir->file), ' ')[0];
					else 
						tmp_redir->file = expand_var(tmp_redir->file);
				}
			}	
			tmp_redir = tmp_redir->next;
		}
		i++;
	}
	/*i = 0;
	while (cmds[i].args)
	{
		while (cmds[i].args)
		{
			printf("--%s--\n",(cmds[i].args)->content);
			//printf("--%c--\n",(cmds[i].args)->token);
			cmds[i].args = (cmds[i].args)->next;
		}
		break;
		i++;
	}
	exit(0);*/
	/*i = 0;
	while (cmds[i].redirs)
	{
		printf("--%s--\n",cmds[i].redirs->file);
		cmds[i].redirs = cmds[i].redirs->next;
	}
	exit(0);*/
	return (cmds);
}
