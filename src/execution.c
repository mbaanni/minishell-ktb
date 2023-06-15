/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:26:32 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/15 15:52:43 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parent_work(int i)
{
	if (i > 0)
	{
		close(g_grl->prev[0]);
		close(g_grl->prev[1]);
	}
	if (i < g_grl->command_count - 1)
	{
		g_grl->prev[0] = g_grl->next[0];
		g_grl->prev[1] = g_grl->next[1];
	}
}

void	wait_for_chiled(int *pid)
{
	int	i;
	int	stats;

	stats = 0;
	i = -1;
	while (++i < g_grl->command_count)
	{
		waitpid(pid[i], &stats, 0);
		if (g_grl->sig != 3)
			g_grl->exit_status = stats >> 8;
	}
}

int	set_pipe_heredoc(int *fd, int i, t_redir *redir)
{
	if (i < g_grl->command_count - 1)
		if (pipe(g_grl->next) == -1)
			return (1);
	*fd = here_doc(redir);
	if (g_grl->_hx == -2)
	{
		g_grl->_hx = -2;
		g_grl->exit_status = 1;
		return (1);
	}
	return (0);
}

void	execute_it(t_command *commands, int *pid, int i, int *fd)
{
	char	**new_env;

	new_env = set_new_env();
	pid[i] = fork();
	if (pid[i] == -1)
		return ;
	if (pid[i] == 0)
		child_work(*fd, i, commands, new_env);
	else
		parent_work(i);
}

void	executing_phase(void)
{
	t_command	*commands;
	int			i;
	int			*pid;
	int			fd;

	i = -1;
	commands = g_grl->command_head;
	pid = my_alloc(sizeof(int) * g_grl->command_count);
	if (g_grl->command_count == 1)
		if (one_cmd(commands))
			return ;
	if (unseted_path(commands->command_path))
		return ;
	while (++i < g_grl->command_count)
	{
		g_grl->sig = 1;
		if (set_pipe_heredoc(&fd, i, commands->command_redirections))
			return ;
		execute_it(commands, pid, i, &fd);
		commands = commands->next;
	}
	wait_for_chiled(pid);
	ft_myalloc_dell(pid);
}
