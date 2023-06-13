/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:17:58 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/08 21:48:45 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <unistd.h>
# include "../libft/get_next_line.h"

int	set_file(char *str)
{
	int	fd[2];

	if (pipe(fd))
		return (-1);
	if (!str)
		str = "";
	write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	return (fd[0]);
}

int	ft_lstrcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*find_in_envs(char *str, int len)
{
	t_env *env;

	env = general->env_head;
	while (env)
	{
		if (!ft_strncmp(env->id, str, len))
		{
			if (ft_strlen(env->id) == len)
				return (env->data);
		}
		env = env->next;
	}
	return (0);
}

int	lent_identifiers(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (i);
	i = 1;
	while (str[i] && str[i] != '=' && str[i] != ' ' && str[i] != '\t')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

char	*expand_for_heredoc(char *str)
{
	int		i;
	int		j;
	char	*exp;
	char	*tmp;

	exp = 0;
	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i + 1] && str[i] == '$' && (str[i + 1] == '?' || (ft_isalpha(str[i + 1]) || str[i + 1] == '_')))
		{
			if (str[i + 1] == '?')
			{
				j = 1;
				exp = ft_itoa(general->exit_status);
			}
			else
			{
				j = lent_identifiers(str + i + 1);
				exp = find_in_envs(str + i + 1, j);
			}
			tmp = ft_strdup(str);
			tmp[i] = 0;
			//will segfault if s2 in strjoin in null
			if (exp)
				tmp = ft_strjoin(tmp, exp);
			str = ft_strjoin(tmp, str + i + j + 1);
			if (!exp)
				i--;
		}
	}
	return (str);
}

int	here_doc(t_redir *redir)
{
	char	*buf;
	char	*str;
	int		fd;

	buf = 0;
	fd = -1;
	while (redir)
	{
		if (redir->token == HERE_DOC)
		{
			fd = -1;
			str = 0;
			while (1)
			{
				if (general->_XH != -1)
					return (-1);
				general->_XH = dup(0);
				write(1, ">", 1);
				buf = get_next_line(general->_XH);
				if(!buf)
					break;
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
			fd = set_file(str);
		}
		redir = redir->next;
	}
	return (fd);
}
