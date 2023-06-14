/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:03:45 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/14 20:20:31 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_erro(t_redir *redir, int fd)
{
	if (redir->is_expand == 2)
	{
		ft_fdprintf(2, "minishell: %s: ambiguous redirect\n", redir->file);
		g_grl->exit_status = 1;
		return (1);
	}
	if (access(redir->file, F_OK) && redir->token != HERE_DOC)
	{
		ft_fdprintf(2, "minishell: %s: No such file or directory\n",
			redir->file);
		g_grl->exit_status = 1;
		return (1);
	}
	if (fd == -1 && redir->token != HERE_DOC)
	{
		ft_fdprintf(2, "minishell: %s: Permission denied\n", redir->file);
		g_grl->exit_status = 1;
		return (1);
	}
	return (0);
}

void	redirect_it(t_redir *redir, int fd, int fdin, int fdout)
{
	if (redir->token == RDIRIN)
	{
		dup2(fd, fdin);
		close(fd);
	}
	if (redir->token == RDIROUT || redir->token == APPEND)
	{
		dup2(fd, fdout);
		close(fd);
	}
}

int	redirection_handler(t_command *commands, int fdin, int fdout)
{
	t_redir	*redir;
	int		fd;
	int		oflags;

	redir = commands->command_redirections;
	while (redir)
	{
		fd = -1;
		oflags = 0;
		if (redir->token == RDIRIN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->token == RDIROUT)
			oflags = O_WRONLY | O_CREAT | O_TRUNC;
		else if (redir->token == APPEND)
			oflags = O_RDWR | O_CREAT | O_APPEND;
		if (oflags && redir->token != RDIRIN)
			fd = open(redir->file, oflags, 0644);
		if (redir_erro(redir, fd))
			return (1);
		redirect_it(redir, fd, fdin, fdout);
		redir = redir->next;
	}
	return (0);
}
