/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:36:10 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/11 22:54:55 by mtaib            ###   ########.fr       */
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

int		check_ambigious(char *str)
{
	char	**args;
	int		i;
	int		state;
	int		count;

	count = 0;
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

t_cmd	*ft_expand(t_cmd *cmds, int nb_cmds)
{
	int		i;
	t_env	*envs;
	t_cmd	*tmp;
	t_lexim	*tmp_lexim;
	t_redir	*tmp_redir;
	t_lexim	*tmp_next;
	char	**args;
	int		j;
	char	*str;

	i = 0;
	envs = general->env_head;
	tmp = cmds;
	while (i < nb_cmds)
	{
		tmp_lexim = cmds[i].args;
		tmp_redir = cmds[i].redirs;
		while (tmp_lexim)
		{
			if (tmp_lexim->prev 
					&& tmp_lexim->prev->token == SPACES 
					&& tmp_lexim->token == WORD 
					&& tmp_lexim->content[0] == '$')
			{
				if (!tmp_lexim->content[1])
					tmp_lexim->content = "\0";
			}
			if (tmp_lexim->token == ENV)
			{
				if (tmp_lexim->content[0] == '"')
				{
					//tmp_lexim->content++;
					//tmp_lexim->content[ft_strlen(tmp_lexim->content) - 1] = '\0';
					tmp_lexim->content = expand_var(tmp_lexim->content);
					//printf("%s\n",tmp_lexim->content);
				}
				else if (tmp_lexim->content[0] != '"' && !check_ambigious(expand_var(tmp_lexim->content)))
				{
					args = ft_split(expand_var(tmp_lexim->content), ' ');
					j = -1;
					tmp_next = tmp_lexim->next;
					tmp_lexim->content = args[0];
					j = 0;
					while (args[++j])	
					{
						//if (j)
						//{
							tmp_lexim->next = new_lexim(ft_strdup(" "));
							tmp_lexim->next->token = SPACES;	
							tmp_lexim->next->next = new_lexim(args[j]);
							if (tmp_lexim->next->next)	
								tmp_lexim = tmp_lexim->next->next;
						//}
					}
					tmp_lexim->next = tmp_next;
				}
				else
				{
						tmp_lexim->content = expand_var(tmp_lexim->content);
				}
			}
			tmp_lexim = tmp_lexim->next;
		}
		while (tmp_redir)
		{
			if (tmp_redir->is_expand)
			{
				/*if (tmp_redir->file && (tmp_redir->file[0] == '"' || check_ambigious(expand_var(tmp_redir->file))))
				{*/
				//printf("|||here =%s|||\n",tmp_redir->file);
				//printf("--%d---\n",check_ambigious(expand_var(tmp_redir->file)));
					if (tmp_redir->file
							&& !check_ambigious(expand_var(tmp_redir->file)))
					{
			
					
						// printf("---%s---\n",tmp_redir->file);
						// printf("---%s---\n",expand_var(tmp_redir->file));
						str = expand_var(tmp_redir->file);
						// if (str)
						str = parse_string(str);
					//	printf("--str = %s--\n",str);
						// printf("---%s---\n",tmp_redir->file);
						
						if (str && !str[0] && should_parse(tmp_redir->file))
								// || (expand_var(tmp_redir->file) && !expand_var(tmp_redir->file)[0])))
							{
								tmp_redir->file = ft_strdup("\0");
							}
						else
							{
								tmp_redir->is_expand = 2;
				 				tmp_redir->file = expand_var(tmp_redir->file);
								break;
							}
						
					}
					

					//if (tmp_redir->token != 'h')
					//{
						/*if (tmp_redir->file[0] == '"')
					{
						//tmp_redir->file++;
						//tmp_redir->file[ft_strlen(tmp_redir->file) - 1] = '\0';			
					}*/
					//printf("%s\n",tmp_redir->file);
				/*	}
				}
				else
					{
						if (tmp_redir->file)
							printf("minishell: %s: ambigious files\n",tmp_redir->file);
					}*/
				/*tmp_redir->file = *///printf("||%s||\n",expand_var(tmp_redir->file));
				else
				{
					//printf("Ok");
					if (tmp_redir->file[0] == '$')
						tmp_redir->file = ft_split(expand_var(tmp_redir->file), ' ')[0];
					else 
						tmp_redir->file = expand_var(tmp_redir->file);
				}
				 //printf("---%s---\n",tmp_redir->file);
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
	}*/
	/*i = 0;
	while (cmds[i].redirs)
	{
		printf("--%s--\n",cmds[i].redirs->file);
		cmds[i].redirs = cmds[i].redirs->next;
	}
	exit(0);*/
	return (cmds);
}
