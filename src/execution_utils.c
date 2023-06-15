/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:48:05 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/15 15:08:51 by mbaanni          ###   ########.fr       */
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
		ft_fdprintf(2, "minishell: %s: No such file or directory\n", str);
		g_grl->exit_status = 127;
		return (1);
	}
	return (0);
}
