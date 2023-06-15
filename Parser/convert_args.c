/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:37:04 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/15 13:02:24 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	should_parse(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
	}
	return (0);
}

void	convert_arguments(t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;
	t_lexim	*tmp_lexim;

	tmp = cmds;
	i = 0;
	while (i < g_grl->command_count && tmp[i].args)
	{
		tmp_lexim = tmp[i].args;
		while (tmp_lexim)
		{
			while (tmp_lexim)
			{
				if (should_parse(tmp_lexim->content))
					tmp_lexim->content = parse_string(tmp_lexim->content);
				tmp_lexim = tmp_lexim->next;
			}
			if (tmp_lexim)
				tmp_lexim = tmp_lexim->next;
		}
		i++;
	}
}

void	convert_redirections(t_cmd *cmds, t_command *tmp_cmd, int i,
		t_list *args)
{
	char	*str;

	while (++i < g_grl->command_count && cmds[i].args)
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
	}
}

void	parse_redirection(int i, t_cmd *tmp)
{
	t_redir	*tmp_redir;

	while (++i < g_grl->command_count && tmp[i].redirs)
	{
		tmp_redir = tmp[i].redirs;
		while (tmp_redir)
		{
			while (tmp_redir)
			{
				if (should_parse(tmp_redir->file) && tmp_redir->is_expand != 2)
				{
					replace_str(tmp_redir->file);
					tmp_redir->file = parse_string(tmp_redir->file);
					if (!(ft_split(tmp_redir->file, 1))[1])
						tmp_redir->file = *ft_split(tmp_redir->file, 1);
				}
				else if (should_parse(tmp_redir->file))
					tmp_redir->file = parse_string(tmp_redir->file);
				tmp_redir = tmp_redir->next;
			}
		}
		if (tmp_redir)
			tmp_redir = tmp_redir->next;
	}
}

t_command	*convert_args(t_cmd *cmds)
{
	t_command	*commands;
	t_command	*tmp_cmd;
	int			i;

	commands = NULL;
	convert_arguments(cmds);
	parse_redirection(-1, cmds);
	i = -1;
	while (++i < g_grl->command_count)
		cmdadd_back(&commands, new_cmd(NULL));
	convert_redirections(cmds, commands, -1, NULL);
	tmp_cmd = commands;
	i = 0;
	while (i < g_grl->command_count && tmp_cmd)
	{
		tmp_cmd->command_redirections = cmds[i].redirs;
		if (tmp_cmd->next)
			tmp_cmd = tmp_cmd->next;
		i++;
	}
	g_grl->command_head = commands;
	return (commands);
}
