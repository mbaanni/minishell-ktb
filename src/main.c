/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:30:50 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/10 12:33:42 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/get_next_line.h"

t_general	*general;

char	*ft_trime_side(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	new = 0;
	j = ft_strlen(str);
	while (str[i] && (str[i] == '	' || str[i] == ' '))
		i++;
	while (j > 0 && (str[j - 1] == '	' || str[j - 1] == ' '))
		j--;
	new = ft_substr(str, i, j - i);
	return (new);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		if (general->_XH != -1)
		{
			close(general->_XH);
			return ;
		}
		else if (!general->sig)
		{
			general->exit_status = 1;
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (sig == SIGQUIT)
	{
		if (general->sig)
			write(1, "Quit: 3\n", 8);
		rl_redisplay();
	}
	if (general->sig)
	{
		general->sig = 3;
		general->exit_status = 128 + sig;
	}
}

void	signal_to_take(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sa, 0);
}

int	main(int ac, char **av, char **ev)
{
	char			*str;
	t_lexim			*lexims;
	struct termios	terminal;

	(void)ac;
	(void)av;
	general = my_alloc(sizeof(t_general));
	if (!general)
		return (0);
	general->sig = 0;
	general->_XH = -1;
	tcgetattr(0, &terminal);
	general->old_c_lflag = terminal.c_lflag;
	general->_terminal = terminal;
	general->ev = ev;
	general->env_head = creat_env(ev);
	signal_to_take();
	while (1)
	{
		general->_terminal.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &general->_terminal);
		general->sig = 0;
		general->_XH = -1;
		if (isatty(0))
		{
			str = readline("minishell> ");
			garbage_collector(str, 0);
		}
		else
			str = ft_strtrim(get_next_line(0), "\n");
		if (!str)
		{
			terminal.c_lflag = general->old_c_lflag;
			tcsetattr(0, TCSANOW, &terminal);
			custom_exit(general->exit_status);
		}
		str = ft_trime_side(str);
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
	return (0);
}
