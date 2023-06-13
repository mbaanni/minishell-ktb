/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:37:04 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/13 12:11:52 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*char	*get_arg(char	*str)
{
	int		i;
	char	*arg;

	i = 0;
	arg = NULL;
	while (str[i] && str[i] != '"' && str[i] != '\'')
			i++;
	if (i)	
		arg = ft_substr(str, 0 , i);
	arg = my_alloc(i + 1);
	i = 0;
	while (str[i] && str[i] != '"' && str[i] != '\'')
	{
		arg[i] = str[i];
		i++;
	}
	arg[i] = '\0';
	return (arg);
}

char	*parse_string(char	*str)
{
	int		i;
	char	c;
	char	s[2];
	char	*s2;

	s2 = NULL;
	i = 0;
	// printf("here = ||%s||\n",str);
	if (!str)
		return (0);
	if (str[i] != '"' && str[i] != '\'')
	{
		s2 = get_arg(str);
	}
	while (str[i] && str[i] != '"' && str[i] != '\'')
		   i++;	
	while (str[i])
	{
		c = str[i++];
		while (str[i] && str[i] != c)
		{
			s[0] = str[i];
			s[1] = '\0';
			s2 = ft_strjoin(s2, s);
			i++;
		}
		i++;
	}
	if (str[i] && (str[i] == '"' || str[i] == '\''))
		i++;
	if (!s2 && str[i] && str[i] != '"' && str[i] != '\'')
	{
		s2 = get_arg(&str[i]);
				
	}
	if (!s2)
	{
		//printf("ok\n");
		return (ft_strdup("\0"));
	}
	return (s2);
}*/

char	*get_arg(char	*str)
{
	int		i;
	char	*arg;

	i = 0;
	while (str[i] && (str[i] != '"' && str[i] != '\''))
			i++;
	arg = ft_substr(str, 0, i);
	/*arg = my_alloc(i + 1);
	i = 0;
	while (str[i] && str[i] != '"' && str[i] != '\'')
	{
		arg[i] = str[i];
		i++;
	}
	arg[i] = '\0';*/
	return (arg);
}

char	*parse_string(char	*str)
{
	int		i;
	char	c;
	char	s[2];
	char	*s2;

	s2 = NULL;
	i = 0;
	if (str[i] != '"' && str[i] != '\'')
		s2 = get_arg(str);
	while (str[i] && str[i] != '"' && str[i] != '\'')
		   i++;
	while (str[i])
	{
		c = str[i++];
		while (str[i] && str[i] != c)
		{
			s[0] = str[i];
			s[1] = '\0';
			s2 = ft_strjoin(s2, s);
			i++;
		}
		if (str[i] && (str[i] == '"' || str[i] == '\''))
			i++;
		while (str[i] && str[i] != '"' && str[i] != '\'')
		{
			s[0] = str[i];
			s[1] = '\0';
			s2 = ft_strjoin(s2, s);
			i++;
		}
	}

	//if (str[i] && str[i] != '"' && str[i] != '\'')
	//	s2 = ft_strjoin(s2, &str[i]);
	if (!s2)
		return (ft_strdup("\0"));
	return (s2);
}

t_command	*new_cmd(char	**args)
{
	t_command *cmd;

	cmd = my_alloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->command_args = args;
	cmd->next = NULL;
	return (cmd);
}

void	cmdadd_back(t_command **cmds, t_command *newcmd)
{
	t_command *tmp;

	tmp = *cmds;
	if (!*cmds)
	{
		*cmds = newcmd;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newcmd;
}

char	**get_args(t_list *cmd)
{
	int		i;
	char	**args;
	t_list 	*tmp;

	tmp = cmd;
	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	args = my_alloc(sizeof(char *) * (i + 1));
	if (!args)
		return (0);
	i = 0;
	while (tmp)
	{
		args[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	/*i = -1;
	while (args[++i])
		printf("%s\n",args[i]);*/
	return (args);
}

int		should_parse(char	*str)
{
	int		i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
	}	
	return (0);
}

t_command	*convert_args(t_cmd *cmds)
{
	t_list	 *args;
	t_command	*commands;
	t_command	*tmp_cmd;
	t_lexim *tmp_lexim;
	t_redir *tmp_redir;
	char	*str;
	int		i;
	t_cmd	*tmp;
	tmp = cmds;	
	commands = NULL;
	i = 0;
	/*while (i < general->command_count)
	{
		while (cmds[i].args)
		{
			printf("%s\n",(cmds[i].args)->content);
			cmds[i].args = (cmds[i].args)->next;
		}
		i++;
	}
	exit(0);*/
	/*while (cmds[i].redirs)
	{
		printf("%s\n",(cmds[i].redirs)->file);
		cmds[i].redirs = (cmds[i].redirs)->next;
	}
	exit(0);*/
	while (i < general->command_count && tmp[i].args)
	{
		tmp_lexim = tmp[i].args;
		while (tmp_lexim)
		{
			while (tmp_lexim)// && tmp_lexim->token == WORD)
			{
				if (should_parse(tmp_lexim->content))
						/*tmp_lexim->content[0] == '"' 
						||  tmp_lexim->content[1] == '\''
						||  tmp_lexim->content[0] == '\'' )*/
					tmp_lexim->content = parse_string(tmp_lexim->content);
				tmp_lexim = tmp_lexim->next;
			}
			if (tmp_lexim)
				tmp_lexim = tmp_lexim->next;
		}
		i++;
	}
	i = 0;
	while (i < general->command_count && tmp[i].redirs)
	{
		tmp_redir = tmp[i].redirs;
		while (tmp_redir)
		{
			while (tmp_redir)
			{
				if (should_parse(tmp_redir->file) && tmp_redir->is_expand != 2)
							/*||  tmp_redir->file[1] == '\''
							||  tmp_redir->file[0] == '\'' )*/
				{
					replace_str(tmp_redir->file);
					tmp_redir->file = parse_string(tmp_redir->file);
					//printf("---%s\n",tmp_redir->file);
					//str = ft_strdup(tmp_redir->file);
					if (!(ft_split(tmp_redir->file, 1))[1])
					{
						tmp_redir->file = *ft_split(tmp_redir->file, 1);
					}
				}
				else if (should_parse(tmp_redir->file))
				{
					tmp_redir->file = parse_string(tmp_redir->file);
				}
				//printf("%s\n",tmp_redir->file);
				tmp_redir = tmp_redir->next;
			}
		}
		if (tmp_redir)
			tmp_redir = tmp_redir->next;
		i++;
	}
	/*tmp_redir = tmp[i].redirs;
	while (tmp_redir)
	{
		printf("%s\n",tmp_redir->file);
		tmp_redir = tmp_redir->next;
	}
	exit(0);*/
	i = 0;
	while (i < general->command_count)
	{
		cmdadd_back(&commands, new_cmd(NULL));
		i++;
	}
	tmp_cmd = commands;
	i = 0;
	while (i < general->command_count && cmds[i].args)
	{
		args = NULL;
		while (cmds[i].args)
		{
				str = NULL;
				while (cmds[i].args && (cmds[i].args)->token != SPACES)
				{
					str = ft_strjoin(str, (cmds[i].args)->content);
					cmds[i].args = (cmds[i].args)->next;
				}
				if (str)
					ft_lstadd_back(&args, ft_lstnew(str));
				if (!cmds[i].args)
					break ;
				cmds[i].args = (cmds[i].args)->next;
		}
		if (args)
		{
			tmp_cmd->command_args = get_args(args);
			tmp_cmd = tmp_cmd->next;
		}
		i++;
	}
	tmp_cmd = commands;
	i = 0;
	while (i < general->command_count && tmp_cmd)
	{
		tmp_cmd->command_redirections = cmds[i].redirs;
		if (tmp_cmd->next)
			tmp_cmd = tmp_cmd->next;
		i++;
	}
	/*tmp_cmd = commands;
	while (tmp_cmd)
	{
		i = -1;
		while (tmp_cmd->command_args && tmp_cmd->command_args[++i])
			printf("%s\n",tmp_cmd->command_args[i]);
		printf("-----REDIRECTIONS-----\n");
		while (tmp_cmd->command_redirections)
		{
			printf("%s is expand %d\n",tmp_cmd->command_redirections->file, tmp_cmd->command_redirections->is_expand);
			tmp_cmd->command_redirections = (tmp_cmd->command_redirections)->next;
		}
		printf("----------\n");
		tmp_cmd = tmp_cmd->next;
	}
	exit(0);*/
	general->command_head = commands;
	return (commands);
}
