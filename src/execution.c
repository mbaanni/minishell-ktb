/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:26:32 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/14 20:21:11 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_file_exist(char *str)
{
	if (opendir(str))
	{
		ft_fdprintf(2, "minishell: %s: is a directory\n", str);
		custom_exit(126);
	}
	if (access(str, F_OK))
	{
		if (ft_strchr(str, '/') || !ft_getenv("PATH"))
			ft_fdprintf(2, "minishell: %s: No such file or directory\n", str);
		else
			ft_fdprintf(2, "minishell: %s: command not found\n", str);
		custom_exit(127);
	}
}

int	one_cmd(t_command *commands)
{
	int	fd;
	int	fdout;

	if (commands->command_path && check_for_built_in(commands, 0)
		&& ft_strncmp("echo", commands->command_path, -1))
	{
		fd = dup(STDIN_FILENO);
		fdout = dup(STDOUT_FILENO);
		if (redirection_handler(commands, fd, fdout))
			return (1);
		check_for_built_in(commands, 1);
		close(fd);
		close(fdout);
		return (1);
	}
	return (0);
}

void	child_work1(t_command *commands)
{
	if (redirection_handler(commands, 0, 1))
		custom_exit(1);
	if (!commands->command_args)
		custom_exit(0);
	if (check_for_built_in(commands, 1))
		custom_exit(g_grl->exit_status);
}

void	child_work(int fd, int i, t_command *commands, char **new_env)
{
	g_grl->_terminal.c_lflag = g_grl->old_c_lflag;
	tcsetattr(0, TCSANOW, &g_grl->_terminal);
	if (fd != -1)
	{
		dup2(fd, 0);
		close(fd);
	}
	else if (i > 0)
	{
		dup2(g_grl->prev[0], 0);
		close(g_grl->prev[0]);
		close(g_grl->prev[1]);
	}
	if (i < g_grl->command_count - 1)
	{
		dup2(g_grl->next[1], 1);
		close(g_grl->next[0]);
		close(g_grl->next[1]);
	}
	child_work1(commands);
	check_file_exist(commands->command_path);
	execve(commands->command_path, commands->command_args, new_env);
	perror(0);
	custom_exit(1);
}

int	unseted_path(char *str)
{
	if (!ft_getenv("PATH") && ft_strncmp("echo", str, 1))
	{
		ft_fdprintf(2, "minishell: %s: No such file or directory\n");
		g_grl->exit_status = 127;
		return (1);
	}
	return (0);
}

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
	if (g_grl->_XH == -2)
	{
		g_grl->_XH = -2;
		g_grl->exit_status = 1;
		return (1);
	}
	return (0);
}

void	executing_phase(void)
{
	t_command	*commands;
	int			i;
	int			fd;
	int			*pid;
	char		**new_env;

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
		new_env = set_new_env();
		g_grl->sig = 1;
		if (set_pipe_heredoc(&fd, i, commands->command_redirections))
			return ;
		pid[i] = fork();
		if (pid[i] == -1)
			return ;
		if (pid[i] == 0)
			child_work(fd, i, commands, new_env);
		else
			parent_work(i);
		commands = commands->next;
	}
	wait_for_chiled(pid);
}
