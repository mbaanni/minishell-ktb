/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:30:50 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/14 20:01:52 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/get_next_line.h"

t_general	*g_grl;

void	signal_to_take(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sa, 0);
}

void	init_general(char **env)
{
	struct termios	terminal;

	g_grl = my_alloc(sizeof(t_general));
	if (!g_grl)
		custom_exit(1);
	g_grl->sig = 0;
	tcgetattr(0, &terminal);
	g_grl->old_c_lflag = terminal.c_lflag;
	g_grl->_terminal = terminal;
	g_grl->ev = env;
	g_grl->env_head = creat_env(env);
}

char	*readstring(void)
{
	char	*str;

	if (isatty(0))
	{
		str = readline("minishell> ");
		garbage_collector(str, 0);
	}
	else
		str = ft_strtrim(get_next_line(0), "\n");
	if (!str)
	{
		g_grl->_terminal.c_lflag = g_grl->old_c_lflag;
		tcsetattr(0, TCSANOW, &g_grl->_terminal);
		custom_exit(g_grl->exit_status);
	}
	return (str);
}

void	start_pr_ex(char *str)
{
	t_lexim	*lexims;

	if (str && str[0])
	{
		add_history(str);
		if (!check_syntax(str))
		{
			lexims = convert_to_lexims(str);
			if (lexims && !check_token_syntax(lexims))
			{
				find_path();
				executing_phase();
			}
		}
	}
}

int	main(int ac, char **av, char **ev)
{
	char	*str;

	(void)ac;
	(void)av;
	init_general(ev);
	signal_to_take();
	while (1)
	{
		g_grl->sig = 0;
		g_grl->_XH = -1;
		g_grl->_terminal.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &g_grl->_terminal);
		g_grl->_XH = -1;
		str = readstring();
		str = ft_trime_side(str);
		start_pr_ex(str);
	}
	return (0);
}
