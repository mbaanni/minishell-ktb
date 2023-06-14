/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:17:58 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/14 17:54:33 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_exp(char *str, int *i)
{
	char	*tmp;
	char	*exp;
	int		j;

	exp = 0;
	if (str[*i + 1] == '?')
	{
		j = 1;
		exp = ft_itoa(g_grl->exit_status);
	}
	else
	{
		j = lent_identifiers(str + *i + 1);
		exp = find_in_envs(str + *i + 1, j);
	}
	tmp = ft_strdup(str);
	tmp[*i] = 0;
	if (exp)
		tmp = ft_strjoin(tmp, exp);
	str = ft_strjoin(tmp, str + *i + j + 1);
	if (!exp)
		(*i)--;
	return (str);
}

char	*expand_for_heredoc(char *str)
{
	int		i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i + 1] && str[i] == '$' && (str[i + 1] == '?'
				|| (ft_isalpha(str[i + 1]) || str[i + 1] == '_')))
		{
			str = get_exp(str, &i);
		}
	}
	return (str);
}

char	*reading_heredoc(t_redir *redir)
{
	char	*buf;
	char	*str;

	buf = 0;
	str = 0;
	while (1)
	{
		if (isatty(0))
			write(1, ">", 1);
		buf = get_next_line(g_grl->_XH);
		if (!buf)
			break ;
		if (buf && buf[ft_strlen(buf) - 1] == '\n')
			buf[ft_strlen(buf) - 1] = 0;
		if (buf)
		{
			if (ft_lstrcmp(buf, redir->file))
				break ;
			if (redir->is_expand == 1)
				buf = expand_for_heredoc(buf);
			buf = ft_strjoin(buf, "\n");
			str = ft_strjoin(str, buf);
		}
	}
	return (str);
}

int	here_doc(t_redir *redir)
{
	char	*str;
	int		fd;

	fd = -1;
	while (redir)
	{
		if (redir->token == HERE_DOC)
		{
			fd = -1;
			if (g_grl->_XH == -2)
				return (-1);
			g_grl->_XH = dup(0);
			str = reading_heredoc(redir);
			close(g_grl->_XH);
			fd = set_file(str);
		}
		redir = redir->next;
	}
	return (fd);
}
