/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:26:32 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/10 14:58:21 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"../includes/minishell.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

int	redirection_handler(t_command *commands, int fdin, int fdout)
{
	int             fd;
	int             oflags;
	t_redir   *redir;

	redir = commands->command_redirections;
	while (redir)
	{
		
		fd = -1;
		oflags = 0;
		if (redir->token == RDIRIN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->token == RDIROUT)
			oflags = O_WRONLY | O_TRUNC | O_CREAT;
		else if (redir->token == APPEND)
			oflags = O_RDWR | O_APPEND | O_CREAT;
		if (oflags && redir->token != RDIRIN)
			fd = open(redir->file, oflags, 0644);
		if (redir->is_expand == 2)
		{
			// if (redir->file[0] || redir->token != RDIROUT)
			ft_fdprintf(2, "minishell: %s: ambiguous redirect\n",redir->file);
			general->exit_status = 1;
			return (1);
		}
		if (access(redir->file, F_OK) && redir->token != HERE_DOC)
		{
			ft_fdprintf(2, "minishell: %s: No such file or directory\n", redir->file);
			general->exit_status = 1;
			return (1);
		}
		if (fd == -1 && redir->token != HERE_DOC)
		{
			ft_fdprintf(2, "minishell: %s: Permission denied\n", redir->file);
			general->exit_status = 1;
			return (1);
		}
		if (redir->token == RDIRIN)
		{
			dup2(fd, fdin);
			close(fd);
		}
		if (oflags && (redir->token == RDIROUT || redir->token == APPEND))
		{
			dup2(fd, fdout);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}

void	check_file_exist(char *str)
{
	if (opendir(str))
	{
		ft_fdprintf(2, "minishell: %s: is a directory\n", str);
		exit(126);
	}
	if (access(str, F_OK))
	{
		if(ft_strchr(str, '/'))
			ft_fdprintf(2, "minishell: No such file or directory\n");
		else
			ft_fdprintf(2, "minishell: command not found\n");
		exit(127);
	}	
}

void executing_phase()
{
	t_command   *commands;
	int			stats;
	int         i;
	int			fd;
	int			fdout;
	int         *pid;
	char		**new_env;

	i = -1;
	stats = 0;
	commands = general->command_head;
	pid = my_alloc(sizeof(int) * general->command_count);
	if (general->command_count == 1)
	{
		if (commands->command_path && ft_strncmp("echo", commands->command_path, -1) && ft_strncmp("pwd", commands->command_path, -1) && check_for_built_in(commands, 0))
		{
			fd = dup(STDIN_FILENO);
			fdout = dup(STDOUT_FILENO);
			if (redirection_handler(commands, 0, 1))
				return ;
			check_for_built_in(commands, 1);
			dup2(fd, 0);
			close(fd);
			dup2(fdout, 1);
			close(fdout);
			return ;
		}
	}
	while(++i < general->command_count)
	{
		new_env = set_new_env();
		if (i < general->command_count - 1)
			pipe(general->next);
		fd = here_doc(commands->command_redirections);
		general->sig = 1;
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (i == 0)
			{
				if (fd)
				{
					dup2(fd, 0);
					close(fd);
				}
			}
			if (i > 0)
			{
				dup2(general->prev[0], 0);
				close(general->prev[0]);
				close(general->prev[1]);
			}
			if (i < general->command_count - 1)
			{
				dup2(general->next[1], 1);
				close(general->next[0]);
				close(general->next[1]);
			}
			if (redirection_handler(commands, 0, 1))
				exit (1);
			if (!commands->command_args)
				exit(0);
			if (check_for_built_in(commands, 1))
				exit(general->exit_status);
			check_file_exist(commands->command_path);
			execve(commands->command_path, commands->command_args, new_env);
				perror(0);
			exit (1);
		}
		else
		{
			if (i > 0)
			{
				close(general->prev[0]);
				close(general->prev[1]);
			}
			if (i < general->command_count - 1)
			{
				general->prev[0] = general->next[0];
				general->prev[1] = general->next[1];
			}
		}
		commands = commands->next;
	}
	i = -1;
	while (++i < general->command_count)
	{
		waitpid(pid[i], &stats, 0);
		general->exit_status = stats >> 8;
	}
}
